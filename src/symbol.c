/*==========================================================================
 * Project: atari cross assembler
 * File: symbol.c
 *
 * Contains symbol table and macro code
 *==========================================================================
 * Created: 12/18/98 mws  split off from asm.c
 * Modifications:
 *    12/19/98   mws  changed to faster hash function
 *    01/01/99   mws  added label/equate/tequate distinction, modified
 *                    string parameter subst of numeric values
 *    06/14/02   mws  added correct scoping for macro labels with the
 *                    same name;  Increased "invoked" lifespan to encompass
 *                    entire macro lifespan
 *    06/15/02   mws  added clean_up to free allocated memory
 *    07/27/03   mws  added multi-pass in case of zp reassignment; added
 *                    better handling of nested macro symbols;
 *    12/30/03   mws  repeat parameter now allows expressions (i.e. 4*10, etc)
 *    05/01/10   mws  add tracking of bank for addrs
 *==========================================================================*
 * TODO: Nothing
 *  When instatiating a macro, prepend label with number and macro name...
 *
 *==========================================================================
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *==========================================================================*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "compat.h"
#include "atasm.h"
#include "symbol.h"
#include "inc_path.h"
#include "atasm_err.h"

macro* macro_list;
macro_call* invoked;
unkLabel* unkLabels;
symbol* hash[HSIZE];

longJump* ljHash[HSIZE];

symbol* linkit();
int repass, double_fwd;

/*=========================================================================*
 * function isUnk
 * parameters: unk, the symbol name to verify
 *
 * A function to determine if a symbol is forward defined
 *=========================================================================*/
unkLabel* isUnk(char* unk) {
	char buf[256];
	unkLabel* walk = unkLabels;

	/* munge macros and local vars */
	if (unk[0] != '=') {
		if (unk[0] == '?') {   /* Munge .LOCAL symbols */
			if (opt.MAElocals)
				snprintf(buf, 256, "%s%s", opt.MAEname, unk);
			else
				snprintf(buf, 256, "=%d=%s", local, unk + 1);
			unk = buf;
		}
		if (invoked) { /* Munge macro symbols... */
			snprintf(buf, 256, "=%.4x_%s=%s", invoked->orig->times, invoked->orig->name, unk);
			unk = buf;
		}
	}
	while (walk) {
		if (!strcmp(walk->label, unk))
			return walk;
		walk = walk->nxt;
	}
	return NULL;
}

/*=========================================================================*
 * function defUnk
 * parameters: unk, the symbol to define; addr, the address to assign
 *
 * A function verify that forward-defined symbols were correctly sized
 * (normally we assume that all forward-referenced symbols are non-zero
 *  page, but this is not always the case...)
 *=========================================================================*/
void defUnk(char* unk, unsigned short addr) {
	if (unk) {
		unkLabel* look = isUnk(unk);
		if (!look)
			return;
		if ((!look->zp) && (addr < 256)) {
			char buf[256];
			char* name = unk;
			if (strchr(name, '=')) {
				name = unk + strlen(unk);
				while (*name != '=')
					name--;
				name++;
			}
			snprintf(buf, 256, "Resizing '%s', forcing another pass", name);
			error(buf, 0);
			look->zp = 1;
			repass++;
		}
		else if (addr > 255) {
			unkLabel* walk = unkLabels;
			while ((walk) && (walk->nxt != look)) {
				walk = walk->nxt;
			}
			if (walk) {
				/* printf("Remove defined %s\n",unk); */
				walk->nxt = walk->nxt->nxt;
				free(look->label);
				free(look);
			}
		}
	}
}

/*=========================================================================*
 * function addUnk
 * parameters: unk, the forward referenced symbol to add
 *
 * A function to track forward defined symbols
 *=========================================================================*/
void addUnk(char* unk) {
	if (unk) {
		char buf[256];
		unkLabel* look;

		/* munge macros and local vars */
		if (unk[0] == '?') {   /* Munge .LOCAL symbols */
			if (opt.MAElocals)
				snprintf(buf, 256, "%s%s", opt.MAEname, unk);
			else
				snprintf(buf, 256, "=%d=%s", local, unk + 1);
			unk = buf;
		}
		if (invoked) { /* Munge macro symbols... */
			snprintf(buf, 256, "=%.4x_%s=%s", invoked->orig->times, invoked->orig->name, unk);
			unk = buf;
		}
		look = isUnk(unk);
		if (!look) {
			unkLabel* u = (unkLabel*)malloc(sizeof(unkLabel));
			if (!u) {
				error("Out of memory allocating symbol.", 1);
			}
			u->nxt = unkLabels;
			u->zp = 0;
			unkLabels = u;
			u->label = (char*)malloc(strlen(unk) + 1);
			if (!u->label) {
				error("Out of memory allocating symbol.", 1);
			}
			strcpy(u->label, unk);
		}
	}
}

/*=========================================================================*
 * function cleanUnk
 * parameters: none
 *
 * A function to clean up forward referenced labels
 *=========================================================================*/
void cleanUnk() {
	unkLabel* kill;
	while (unkLabels) {
		kill = unkLabels;
		unkLabels = unkLabels->nxt;
		free(kill->label);
		free(kill);
	}
}

/*=========================================================================*
 * function fixRepass
 * parameters: none
 *
 * clear symbol table if multipass is necessary
 *=========================================================================*/
void fixRepass() {
	symbol* sym;
	macro_line* macl, * killml;
	macro* mac, * killm;

	/* Clear memory bitmap */
	clear_banks();

	sym = linkit();  /* Free symbol table entries... */
	while (sym) {
		if ((sym->tp != OPCODE) && (sym->tp != DIRECT)) {
			symbol* kill = sym;
			sym = sym->lnk;
			/* Retain all labels, equates, and temp equates(?) that are zero page */
			if ((kill->tp == MACROL) || (kill->tp == MACRON) || (kill->tp == MACROQ)
				|| (kill->addr > 0xff))
				kill->name[0] = 0;
			/*	remsym(kill);       */
		}
		else {
			sym = sym->lnk;
		}
	}

	mac = macro_list;  /* Free macro definitions... */
	while (mac) {
		macl = mac->lines;
		while (macl) {
			free(macl->line);
			killml = macl;
			macl = macl->nxt;
			free(killml);
		}
		killm = mac;
		mac = mac->nxt;
		free(killm);
	}
	macro_list = NULL;
}
/*=========================================================================*
  Hashing function described in
  "Fast Hashing of Variable-Length Text Strings,"
  by Peter K. Pearson, CACM, June 1990.
  Pseudorandom Permutation of the Integers 0 through 255: Table from p. 678.
 *=========================================================================*/
static unsigned randomNumbers[] = {
  1, 14,110, 25, 97,174,132,119,138,170,125,118, 27,233,140, 51,
  87,197,177,107,234,169, 56, 68, 30,  7,173, 73,188, 40, 36, 65,
  49,213,104,190, 57,211,148,223, 48,115, 15,  2, 67,186,210, 28,
  12,181,103, 70, 22, 58, 75, 78,183,167,238,157,124,147,172,144,
  176,161,141, 86, 60, 66,128, 83,156,241, 79, 46,168,198, 41,254,
  178, 85,253,237,250,154,133, 88, 35,206, 95,116,252,192, 54,221,
  102,218,255,240, 82,106,158,201, 61,  3, 89,  9, 42,155,159, 93,
  166, 80, 50, 34,175,195,100, 99, 26,150, 16,145,  4, 33,  8,189,
  121, 64, 77, 72,208,245,130,122,143, 55,105,134, 29,164,185,194,
  193,239,101,242,  5,171,126, 11, 74, 59,137,228,108,191,232,139,
  6, 24, 81, 20,127, 17, 91, 92,251,151,225,207, 21, 98,113,112,
  84,226, 18,214,199,187, 13, 32, 94,220,224,212,247,204,196, 43,
  249,236, 45,244,111,182,153,136,129, 90,217,202, 19,165,231, 71,
  230,142, 96,227, 62,179,246,114,162, 53,160,215,205,180, 47,109,
  44, 38, 31,149,135,  0,216, 52, 63, 23, 37, 69, 39,117,146,184,
  163,200,222,235,248,243,219, 10,152,131,123,229,203, 76,120,209
};
/*=========================================================================*
 * function hashit(char *name)
 * parameters: name - the string to hash
 *
 * A function to take a string and generates a number between 0-HSIZE
 *=========================================================================*/
int hashit(char* name) {
	int hash1 = 0;
	int hash2 = 0;

	while (*name != 0) {
		/* Hash function is XOR of successive characters, randomized by
		 * the hash table. */
		hash1 ^= randomNumbers[(int)*name++];
		if (*name != 0)
			hash2 ^= randomNumbers[(int)*name++];
	}
	return ((hash1 << 8) | hash2) % HSIZE;
}
/*=========================================================================*
 * function findsym(char *name)
 * parameters: name - the name of the symbol to find
 *
 * Looks up a given word and returns either the correct structure or a NULL
 * if the word is unknown.
 *=========================================================================*/
symbol* findsym(char* name) {
	int i;
	symbol* walk;
	macro_call* stack = invoked;
	char nbuf[256], buf[256], * look;

	if (name[0] == '?') {   /* Munge .LOCAL symbols */
		if (opt.MAElocals)
			snprintf(nbuf, 256, "%s%s", opt.MAEname, name);
		else
			snprintf(nbuf, 256, "=%d=%s", local, name + 1);
		name = nbuf;
	}
	while (1) {
		if (stack) { /* Munge macro symbols... */
			snprintf(buf, 256, "=%.4x_%s=%s", stack->orig->times, stack->orig->name, name);
			look = buf;
		}
		else
			look = name;

		i = hashit(look);      /* Find word index */
		walk = hash[i];        /* Get initial pointer */
		while (walk) {       /* Search list for word */
			if (!strcmp(walk->name, look)) {
				return walk;
			}
			walk = walk->nxt;
		}
		if (stack)        /* Inside a macro, crawl up stack, then normal */
			stack = stack->nxt;
		else
			break;
	}

	return NULL;
}
/*=========================================================================*
 * function addsym(symbol *wrd)
 * parameters: wrd - the symbol to add
 *
 * This function adds a word to the hashtable, if the word finds a unique
 * slot, it returns a 1, otherwise it returns a 2
 *=========================================================================*/
int addsym(symbol* wrd) {
	int i;
	symbol* walk;

	i = hashit(wrd->name);      /* Hash word to get index */
	walk = hash[i];
	if (!walk) {              /* First word at this location */
		hash[i] = wrd;
		return 1;
	}
	while (walk->nxt)         /* Otherwise, traverse list to end */
		walk = walk->nxt;
	walk->nxt = walk->lnk = wrd;  /* and finally add word to list */
	return 2;
}
/*=========================================================================*
 * function remsym(symbol *wrd)
 * parameters: wrd - the symbol to remove
 *
 * This function removes a symbol from the hashtable
 *=========================================================================*/
void remsym(symbol* wrd) {
	int i;
	symbol* walk, * lst;

	i = hashit(wrd->name);
	walk = hash[i];
	lst = NULL;
	while (walk) {
		if (!strcmp(wrd->name, walk->name)) {
			symbol* hold = walk->nxt;

			if (lst)
				lst->nxt = hold;
			else
				hash[i] = hold;

			free(wrd->name);
			free(wrd);

			walk = hold;
			continue;
		}
		lst = walk;
		walk = walk->nxt;
	}
}
/*=========================================================================*
 * function get_sym
 * creates and initializes a new symbol entry structure.
 *=========================================================================*/
symbol* get_sym() {
	symbol* sym;

	sym = (symbol*)malloc(sizeof(symbol));
	if (!sym) {
		error("Out of memory allocating new symbol.", 1);
	}
	sym->nxt = sym->lnk = sym->mlnk = NULL;
	sym->orig = sym->name = sym->macroShadow = NULL;
	sym->ref = sym->tp = sym->addr = sym->bank = sym->num = 0;

	sym->lineNr = 0;
	sym->ftrack = NULL;
	sym->comment = NULL;
	sym->dumpOptions = 0;

	return sym;
}
/*=========================================================================*
 * function linkit:
 *  This function updates the link pointers of all the entries in the hash
 * table, creating a single linked list.
 *=========================================================================*/
symbol* linkit() {
	symbol* clist, * walk;
	int i = 0;

	clist = walk = NULL;
	while ((i < HSIZE) && (!hash[i]))
		i++;

	if (i == HSIZE)
		return NULL;

	clist = walk = hash[i];

	while (i < HSIZE) {  /* Walk through all indices of hash table */
		while (walk->nxt) {
			walk->lnk = walk->nxt;
			walk = walk->nxt;
		}
		walk->lnk = NULL;
		i++;
		while ((i < HSIZE) && (!hash[i]))
			i++;
		if (i < HSIZE) {
			walk->lnk = hash[i];
			walk = hash[i];
		}
	}
	return clist;
}
/*==========================================================================*
 * procedure alpha_merge
 * Part of the merge sort function, this does the actual merge...
 * sorts list alphabetically.
 *==========================================================================*/
symbol* alpha_merge(symbol* p, symbol* q) {
	symbol* r, * l;

	if ((strcmp(p->name, q->name) < 0)) {
		r = p;
		p = p->lnk;
	}
	else {
		r = q;
		q = q->lnk;
	}
	l = r;
	while ((p) && (q))
		if ((strcmp(p->name, q->name) < 0)) {
			r->lnk = p;
			r = p;
			p = p->lnk;
		}
		else {
			r->lnk = q;
			r = q;
			q = q->lnk;
		}
	if (!p)
		r->lnk = q;
	else
		r->lnk = p;
	return (l);
}
/*==========================================================================*
 * procedure address_merge
 * Part of the merge sort function, this does the actual merge...
 * sorts list by address.
 *==========================================================================*/
symbol* address_merge(symbol* p, symbol* q)
{
	symbol* r, * l;

	if (p->addr < q->addr) {
		r = p;
		p = p->lnk;
	}
	else {
		r = q;
		q = q->lnk;
	}
	l = r;
	while ((p) && (q))
		if (p->addr < q->addr) {
			r->lnk = p;
			r = p;
			p = p->lnk;
		}
		else {
			r->lnk = q;
			r = q;
			q = q->lnk;
		}
	if (!p)
		r->lnk = q;
	else
		r->lnk = p;
	return l;
}
/*==========================================================================*
 * function sort
 * This function sorts the symbol definition linked list alphabetically
 * or by address
 *==========================================================================*/
symbol* sort(symbol* head, int byAddress) {
	symbol* p, * q, * stack[128];
	int i, c, merge, d;

	p = head;
	c = 0;
	while (p) {
		c++;
		i = c;
		merge = 0;
		while (!(i & 1)) {
			i /= 2;
			merge++;
		}
		q = p;
		p = p->lnk;
		q->lnk = NULL;
		for (i = 0; i <= merge - 1; i++) {
			q = byAddress ? address_merge(q, stack[i]) : alpha_merge(q, stack[i]);
		}
		stack[merge] = q;
	}
	merge = -1;
	while (c) {
		d = c & 1;
		c = c / 2;
		merge++;
		if (d) {
			if (p) {
				p = byAddress ? address_merge(p, stack[merge]) : alpha_merge(p, stack[merge]);
			}
			else {
				p = stack[merge];
			}
		}
	}
	return p;
}
/*=========================================================================*
 * function dump_symbols
 * prints out all symbols entered into the symbol table
 *=========================================================================*/
int dump_symbols() {
	symbol* sym, * head;
	int n;

	head = linkit();
	if (!head)
		return 0;
	head = sym = sort(head, 0);
	n = 0;
	printf("\nEquates:\n");
	while (sym) {
		if (sym->name[0])
			if (((sym->tp == EQUATE) || (sym->tp == TEQUATE)) && (sym->name[0] != '=')) {
				printf("%c%s: %.4x\t\t", (sym->tp == TEQUATE) ? '*' : ' ',
					sym->name, sym->addr & 0xffff);
				n++;
				if (n == 3) {
					printf("\n");
					n = 0;
				}
			}
		sym = sym->lnk;
	}
	sym = head;
	printf("\n\nSymbol table:\n");
	while (sym) {
		if (sym->name[0])
			if ((sym->tp == LABEL) && (sym->name[0] != '=')) {
				if ((strchr(sym->name, '?')) && (opt.MAElocals))
					;
				else {
					printf("%s: %.4x\t\t", sym->name, sym->addr & 0xffff);
					n++;
					if (n == 3) {
						printf("\n");
						n = 0;
					}
				}
			}
		sym = sym->lnk;
	}
	printf("\n");
	return 0;
}
/*=========================================================================*
 * function dump_labels
 * prints out all symbols entered into the symbol table in label format
 *=========================================================================*/
int dump_labels(char* fname) {
	symbol* sym, * head;
	FILE* out;

	out = fopen(fname, "wb");
	if (!out)
		return 0;

	head = linkit();
	if (!head) {
		fclose(out);
		return 0;
	}
	head = sym = sort(head, 0);

	while (sym) {
		if (sym->name[0])
			if ((sym->tp == LABEL) && (sym->name[0] != '=')) {
				if ((strchr(sym->name, '?')) && (opt.MAElocals))
					fprintf(out, "%.4x %s\n", sym->addr & 0xffff, sym->name);
				else {
					fprintf(out, "%.4x %s\n", sym->addr & 0xffff, sym->name);
				}
			}
		sym = sym->lnk;
	}
	fclose(out);
	return 0;
}

/*=========================================================================*
 * function dump_c_header
 * prints out all symbols entered into the symbol table in c header format
 *=========================================================================*/
int dump_c_header(char* header_fname, char* asm_fname)
{
	symbol* sym, * head;
	char cheader_name[256];
	char base_name[256];
	char* runner;
	FILE* out;

	file_tracking* last_tracked_filename = NULL;
	int maxLength;

	/* Generate the #if check name */
	for (runner = asm_fname + strlen(asm_fname); runner >= asm_fname; runner--)
	{
		if (*runner == '/' || *runner == '\\')
			break;
	}

	if (runner >= asm_fname) {
		strcpy(cheader_name, runner + 1);
	}
	else {
		/* There is no delimiter: the entire string must be a filename. */
		strcpy(cheader_name, asm_fname);
	}

	/* Find the basename of the file (no extension). We stop at the first . */
	for (runner = cheader_name; *runner && *runner != '.'; ++runner);
	memset(base_name, 0, sizeof(base_name));
	strncpy(base_name, cheader_name, (char*)runner - cheader_name);

	/* Figure out the ifndef name for the header file */
	for (runner = cheader_name; *runner; ++runner) {
		*runner = toupper(*runner);
		if (*runner == '.')
			*runner = '_';
	}

	for (runner = base_name; *runner; ++runner) {
		*runner = toupper(*runner);
	}

	out = fopen(header_fname, "wb");
	if (!out)
		return 0;

	fprintf(out, "#ifndef _%s_\n", cheader_name);
	fprintf(out, "#define _%s_\n\n", cheader_name);

	head = linkit();
	if (!head) {
		fclose(out);
		return 0;
	}
	head = sym = sort(head, 1); /* sort by address */

	/* Lets find the max length of the BASE_SYMBOL entry */
	maxLength = 0;

	while (sym)
	{
		if ((sym->tp == EQUATE || sym->tp == LABEL) && sym->name[0] && sym->name[0] != '=')
		{
			int len = (int)strlen(sym->name);
			if (len > maxLength) maxLength = len;
		}
		sym = sym->lnk;
	}

	fprintf(out, "/* Constants */\n");
	sym = head;
	while (sym)
	{
		if (sym->name[0])
		{
			if (sym->tp == EQUATE)
			{
				fprintf(out, "#define %s_%-*s 0x%.4X /* %s @ %d */\n", base_name, maxLength, sym->name, sym->addr & 0xffff, sym->ftrack ? ((sym->ftrack == last_tracked_filename) ? "\"" : sym->ftrack->name) : "", sym->lineNr);
				last_tracked_filename = sym->ftrack;
			}
		}
		sym = sym->lnk;
	}

	fprintf(out, "\n/* Labels */\n");
	sym = head;
	last_tracked_filename = NULL;
	while (sym)
	{
		if (sym->name[0])
		{
			if ((sym->tp == LABEL) && (sym->name[0] != '='))
			{
				fprintf(out, "#define %s_%-*s 0x%.4X /* %s @ %d */\n", base_name, maxLength, sym->name, sym->addr & 0xffff, sym->ftrack ? ((sym->ftrack == last_tracked_filename) ? "\"" : sym->ftrack->name) : "", sym->lineNr);
				last_tracked_filename = sym->ftrack;
			}
		}
		sym = sym->lnk;
	}

	fprintf(out, "\n#endif\n");
	fclose(out);
	return 0;
}

/*=========================================================================*
 * function dump_assembler_header
 * prints out all equates and symbols entered into the symbol table in
 * atasm equate format
 *=========================================================================*/
int dump_assembler_header(char* header_fname)
{
	symbol* sym, * head;
	FILE* out;
	file_tracking* last_tracked_filename = NULL;
	int maxLength;

	out = fopen(header_fname, "wb");
	if (!out)
		return 0;

	head = linkit();
	if (!head) {
		fclose(out);
		return 0;
	}
	head = sym = sort(head, 1);

	/* Lets find the max length of the BASE_SYMBOL entry */
	maxLength = 0;

	while (sym)
	{
		if ((sym->tp == EQUATE || sym->tp == LABEL) && sym->name[0] && sym->name[0] != '=')
		{
			int len = (int)strlen(sym->name);
			if (len > maxLength) maxLength = len;
		}
		sym = sym->lnk;
	}

	fprintf(out, "\n; CONSTANTS\n");
	sym = head;
	while (sym)
	{
		if (sym->tp == EQUATE && sym->name[0] && sym->name[0] != '=')
		{
			fprintf(out, "%-*s = $%.4X ; %s @ %d\n", maxLength, sym->name, sym->addr & 0xffff, sym->ftrack ? ((sym->ftrack == last_tracked_filename) ? "\"" : sym->ftrack->name) : "", sym->lineNr);
			last_tracked_filename = sym->ftrack;
		}
		sym = sym->lnk;
	}

	fprintf(out, "\n; LABELS\n");
	sym = head;
	last_tracked_filename = NULL;
	while (sym)
	{
		if (sym->tp == LABEL && sym->name[0] && sym->name[0] != '=')
		{
			fprintf(out, "%-*s = $%.4X ; %s @ %d\n", maxLength, sym->name, sym->addr & 0xffff, sym->ftrack ? ((sym->ftrack == last_tracked_filename) ? "\"" : sym->ftrack->name) : "", sym->lineNr);
			last_tracked_filename = sym->ftrack;
		}
		sym = sym->lnk;
	}

	fclose(out);
	return 0;
}

/*=========================================================================*
 * function dump_VSCode
 * prints out info in VSCode plugin format
 *=========================================================================*/
char* bestNameForSymbol(symbol* sym)
{
	static char* ptrNone = "";
	if (sym == NULL || sym->name == NULL || sym->name[0] == 0) return ptrNone;
	if (sym->name[0] == '=')
		return sym->orig;
	return sym->name;
}

// Find all " and convert them to \"
// Convert all \t (tab) characters to ' '/space
char* encodeStringForJson(char* src)
{
	static char buffer[1024];

	if (src == NULL) {
		buffer[0] = 0;
		return buffer;
	}

	char* dest = buffer;
	while (*src != 0) {
		if (*src == '"') {
			*dest = '\\';
			++dest;
			*dest = *src;
		}
		else  if (*src == '\t') {
			*dest = ' ';
		}
		else
			*dest = *src;
		++dest;
		++src;
	}
	*dest = 0;

	return buffer;

}

/*
* trackedFiles: linked list of files that have been included
* parts: which data is to be dumped (CONSTANTS, LABEL, MACROS)
*/
void dump_VSCode(file_tracking* trackedFiles, int parts)
{
	symbol* sym, * head;
	FILE* out;
	int count;

	out = fopen("asm-symbols.json", "wb");
	if (!out)
		return;

	head = linkit();
	if (!head) {
		fprintf(out, "{}");
		fclose(out);
		return;
	}
	head = sym = sort(head, 1);

	fprintf(out, "{\n");

	// Constants
	fprintf(out, "\"constants\":[\n");
	if (parts & DUMP_CONSTANTS)
	{
		sym = head;
		count = 0;
		while (sym)
		{
			if (sym->tp == EQUATE && sym->dumpOptions == 0)// && sym->name[0] && sym->name[0] != '=')
			{
				if (count != 0)
					fprintf(out, ",\n");
				fprintf(out, "{");
				fprintf(out, "\"name\":\"%s\"", bestNameForSymbol(sym));
				fprintf(out, ",\"addr\":%d", sym->addr & 0xffff);
				fprintf(out, ",\"file\":\"%s\"", sym->ftrack ? sym->ftrack->name : "-");
				fprintf(out, ",\"ln\":%d", sym->lineNr);
				if (sym->comment) {
					fprintf(out, ",\"com\":\"%s\"", encodeStringForJson(sym->comment));
				}
				fprintf(out, "}");
				++count;
			}
			sym = sym->lnk;
		}
	}
	fprintf(out, "\n]\n");

	// Labels
	fprintf(out, ",\"labels\":[\n");
	if (parts & (DUMP_LABELS_ALL | DUMP_LABELS_PRIMARY))
	{
		int skipLocalLabels = parts & DUMP_LABELS_PRIMARY;

		sym = head;
		count = 0;
		for (sym = head; sym; sym = sym->lnk)
		{
			if (sym->tp == LABEL) // && sym->name[0] && sym->name[0] != '=')
			{
				if (skipLocalLabels && sym->name[0] == '=')
					continue;
				if (count != 0)
					fprintf(out, ",\n");
				fprintf(out, "{");
				fprintf(out, "\"name\":\"%s\"", bestNameForSymbol(sym));
				fprintf(out, ",\"addr\":%d", sym->addr & 0xffff);
				if (sym->lineNr > 0)
				{
					fprintf(out, ",\"file\":\"%s\"", sym->ftrack ? sym->ftrack->name : "-");
					fprintf(out, ",\"ln\":%d", sym->lineNr);
				}
				else {
					fprintf(out, ",\"cmdln\":\"%s\"", sym->orig);
				}
				if (sym->comment) {
					fprintf(out, ",\"com\":\"%s\"", encodeStringForJson(sym->comment));
				}
				fprintf(out, "}");
				++count;
			}

		}
	}
	fprintf(out, "\n]\n");

	/* MACROS */
	fprintf(out, ",\"macros\":[\n");
	if (parts & DUMP_MACROS)
	{
		sym = head;
		count = 0;
		while (sym)
		{
			if (sym->tp == MACRON) // && sym->name[0] && sym->name[0] != '=')
			{
				if (count != 0)
					fprintf(out, ",\n");
				fprintf(out, "{");
				fprintf(out, "\"name\":\"%s\"", bestNameForSymbol(sym));
				// fprintf(out, ",\"addr\":%d", sym->addr & 0xffff);
				if (sym->lineNr > 0)
				{
					fprintf(out, ",\"file\":\"%s\"", sym->ftrack ? sym->ftrack->name : "-");
					fprintf(out, ",\"ln\":%d", sym->lineNr);
				}
				if (sym->comment) {
					fprintf(out, ",\"com\":\"%s\"", encodeStringForJson(sym->comment));
				}
				fprintf(out, "}");
				++count;
			}
			sym = sym->lnk;
		}
	}
	fprintf(out, "\n]\n");

	/* Included files */
	fprintf(out, ",\"includes\":[\n");
	sym = head;
	count = 0;
	while (trackedFiles)
	{
		if (count != 0)
			fprintf(out, ",\n");
		fprintf(out, "{");
		fprintf(out, "\"file\":\"%s\"", trackedFiles->name);
		fprintf(out, "}");
		++count;
		trackedFiles = trackedFiles->nxt;
	}
	fprintf(out, "\n]\n");


	fprintf(out, "}\n");
	fclose(out);
}

/*=========================================================================*
  function get_macro_call
  parameter: name- name of macro to find

  returns a macro_call structure or NULL if not found
 *=========================================================================*/
macro_call* get_macro_call(char* name) {
	macro* walk;
	macro_call* call;

	walk = macro_list;
	while (walk) {
		if (!strcmp(name, walk->name)) {
			call = (macro_call*)malloc(sizeof(macro_call));
			if (!call) {
				error("Out of memory allocating macro.", 1);
			}
			call->argc = 0;
			call->orig = walk;
			call->cmd = NULL;
			call->nxt = NULL;
			call->line = walk->lines;
			return call;
		}
		walk = walk->nxt;
	}
	return NULL;
}
/*=========================================================================*
 * function macro_subst(char *buf, char *cmd)
 * parameters: buf - the line to process
 *             cmd - the command line invocation
 *
 * replaces macro parameters with the appropriate values
 *=========================================================================*/
int macro_subst(char* name, char* in, macro_line* args, int max) {
	char buf[256], num[256], * look, * walk;
	int i, pnum, stype, ltype;
	symbol* sym;
	macro_line* cmd;

	if (!strchr(in, '%'))
		return 0;

	memset(buf, 0, 256);
	walk = buf;
	look = in;
	/* Format for macro subst:
	   %<num>:  parameter is an expression  (paramter # is decimal)
	   %$<num>: parameter is a string       (paramter # is decimal)
	   %(LABEL): parameter is an expression (paramter # is label addr)
	   %$(LABEL): parameter is a string     (paramter # is label addr)
	*/
	while (*look) {
		if (*look == '%') { /* time to substitute a paramter */
			if (*(look + 1) == '%') {
				*walk++ = *look++;
				*walk++ = *look++;
			}
			else if ((*(look + 1) == '$') || (ISDIGIT(*(look + 1))) ||
				(*(look + 1) == '(') || ((*(look + 1) == '$') && (*(look + 2) == '('))) {
				look++;
				stype = ltype = 0;

				if (*look == '(') {
					look++;
					ltype = 1;
				}
				else if (*look == '$') {
					stype = 1;
					look++;
					if (*look == '(') {
						look++;
						ltype = 1;
					}
				}
				i = 0;
				if (ltype) {  /* Get label value for parameter idx */
					while ((*look) && (*look != ')') && (i < 255))
						num[i++] = *look++;
					if (i == 256)
						error("Label overflow in macro parameter", 1);
					if (*look == ')')
						look++;
					num[i] = 0;
					sym = findsym(num);
					if (!sym) {
						snprintf(buf, 256, "Reference to undefined label '%s' in macro", num);
						error(buf, 1);
					}
					if ((sym->tp != LABEL) && (sym->tp != MACROL) && (sym->tp != MACROQ) &&
						(sym->tp != EQUATE) && (sym->tp != TEQUATE))
						error("Illegal label type in macro parameter", 1);
					pnum = sym->addr;
				}
				else {  /* Normal parameter idx */
					while ((ISDIGIT(*look)) && (i < 15))
						num[i++] = *look++;
					if (i == 15)
						error("Number overflow in macro parameter", 1);
					num[i] = 0;
					sscanf(num, "%d", &pnum);
				}

				if (pnum == 0) {
					if (stype) {
						snprintf(num, 256, "\"%s\"", name);
						strcpy(walk, num);  /* return macro name */
					}
					else {
						snprintf(num, 256, "%d", max);         /* return # parameters */
						strcpy(walk, num);
					}
					walk = buf + strlen(buf);
				}
				else {
					pnum--;
					if (pnum < max) {
						cmd = args;
						while (pnum) {
							cmd = cmd->nxt;
							pnum--;
						}
						if ((cmd->line[0] == '"') && (!stype)) {  /* numeric value for string */
							int len = (int)strlen(cmd->line) - 2;
							snprintf(num, 256, "%d", len); /* return str len */
							strcpy(walk, num);
						}
						else if ((cmd->line[0] != '"') && (stype)) { /* string val for num */
							/* FIXME to return correct string name--any rules for this?*/
							i = 0;
							while ((cmd->line[i]) && !ISALPHA(cmd->line[i]))
								i++;
							get_name(cmd->line + i, walk);
						}
						else
							strcpy(walk, cmd->line);   /* normal subst */

						walk = buf + strlen(buf);
					}
					else
						error("Not enough parameters passed to macro.", 1);
				}
			}
			else error("Invalid macro parameter reference.", 1);
		}
		else {
			*walk++ = *look++;
		}
	}
	*walk = 0;
	strcpy(in, buf);

	return 1;
}
/*=========================================================================*
  function create_macro(symbol *sym)

  creates a macro entry in the macro table
 *=========================================================================*/
int create_macro(symbol* sym) {
	char* str;
	macro* m;
	macro_line* line, * tail;
	symbol* entry;
	char* up;

	// Check if there is a comment for the macro
	char* comment = NULL;
	str = get_nxt_word(PEEK_COMMENT);
	if (str)
	{
		comment = STRDUP(str);
	}

	str = get_nxt_word(PARSE_NEXT_LINE);
	if (!str)
		error("No macro name specified.", 1);
	m = (macro*)malloc(sizeof(macro));
	m->mlabels = NULL;
	m->times = 0;
	m->nxt = NULL;
	m->lines = NULL;
	m->num = m->tp = 0;

	entry = get_sym();
	/* Set the original name of the symbol, nothing is processed yet */
	entry->orig = STRDUP(str);
	entry->lineNr = fin->line;
	entry->ftrack = fin->ftrack;
	entry->comment = comment;

	entry->tp = MACRON;
	entry->name = m->name = (char*)malloc(strlen(str) + 1);
	strcpy(m->name, str);
	up = m->name;
	while (*up) {
		*up = TOUPPER(*up);
		up++;
	}
	if (findsym(entry->name)) {
		char err[256];
		symbol* s = findsym(entry->name);
		if (s->tp == OPCODE) {
			snprintf(err, 256, "Cannot use opcode as macro name.\n");
		}
		else if (s->tp == MACRON) {
			snprintf(err, 256, "Macro '%s' already defined.\n", entry->name);
		}
		else {
			snprintf(err, 256, "Invalid macro name '%s', name already in use.\n", entry->name);
		}
		error(err, 1);
	}
	addsym(entry);
	tail = NULL;

	while (1) {
		str = get_nxt_word(PARSE_NEXT_LINE);
		if (!str)
			error("Unterminated Macro", 1);

		if (!STRCASECMP(str, ".ENDM"))
			break;
		if (!STRCASECMP(str, ".MACRO"))
			error("No nested macro definitions.", 1);

		str = get_nxt_word(PARSE_CURRENT_LINE);  /* Retrieve entire line */
		get_nxt_word(PARSE_LINE_REST);      /* Reset line to force read */
		m->num++;
		line = (macro_line*)malloc(sizeof(macro_line));
		if (!line) {
			error("Out of memory allocating macro.", 1);
		}
		line->nxt = 0;
		line->line = (char*)malloc(strlen(str) + 1);
		if (!line->line) {
			error("Out of memory allocating macro.", 1);
		}
		strcpy(line->line, str);
		if (!m->lines)
			m->lines = tail = line;
		else {
			tail->nxt = line;
			tail = line;
		}
	}

	m->num++;  /* Now add dummy line to force membership of last line */
	line = (macro_line*)malloc(sizeof(macro_line));
	line->nxt = 0;
	line->line = (char*)malloc(2);
	strcpy(line->line, " ");
	if (!m->lines)
		m->lines = tail = line;
	else {
		tail->nxt = line;
		tail = line;
	}

	m->nxt = macro_list;
	macro_list = m;

	return 1;
}
/*=========================================================================*
 * function macro_param(macro_call *mc, char *cmd)
 * parameters: mc- the maco instance
 *             cmd- the command line
 *
 *  builds the arg command table for a particular macro invokation
 *=========================================================================*/
int macro_param(macro_call* mc, char* cmd) {
	int n;
	char* param;
	macro_line* line, * tail;
	n = 0;
	tail = NULL;

	get_nxt_word(PARSE_REPLACE_COMMAS); /* replace commas */
	while (1) {
		param = get_nxt_word(PARSE_NEXT_WORD);
		if (!strlen(param)) {
			mc->argc = n;
			return 0;
		}
		n++;
		line = (macro_line*)malloc(sizeof(macro_line));
		if (!line) {
			error("Out of memory allocting macro paramter.", 1);
		}
		line->nxt = 0;
		line->line = (char*)malloc(strlen(param) + 1);
		if (!line->line) {
			error("Out of memory allocting macro paramter.", 1);
		}
		strcpy(line->line, param);
		if (!mc->cmd)
			mc->cmd = tail = line;
		else {
			tail->nxt = line;
			tail = line;
		}
	}

}
/*=========================================================================*
 * function skip_macro()
 *
 * this skips a macro defintion
 *=========================================================================*/
int skip_macro() {
	char* str;

	while (1) {
		str = get_nxt_word(PARSE_NEXT_LINE);
		if (!STRCASECMP(str, ".ENDM"))
			break;
	}
	return 1;
}
/*=========================================================================*
 * function clear_ref()
 *
 * this clears reference field, and resets macro counts
 *=========================================================================*/
int clear_ref() {
	symbol* walk;
	macro* mwalk;
	int i;

	for (i = 0; i < HSIZE; i++) {
		walk = hash[i];
		while (walk) {
			walk->ref = walk->num = 0;
			walk = walk->nxt;
		}
	}

	mwalk = macro_list;

	while (mwalk) {
		mwalk->times = 0;
		mwalk = mwalk->nxt;
	}

	return 0;
}
/*=========================================================================*
 * function do_rept()
 *
 * this creates the repeat macro
 *=========================================================================*/
int do_rept(symbol* sym) {
	char* str;
	macro* m;
	macro_line* line, * tail;
	macro_call* rept;
	unsigned int num;

	str = get_nxt_word(PARSE_NEXT_LINE);
	if (!str)
		error("No repetition parameter specified.", 1);

	squeeze_str(str);
	num = get_expression(str, 0);
	if (num == 0xffff)
		error("Malformed repeat value.", 1);

	/*  if ((!ISDIGIT(str[0]))&&(str[0]!='$'))
		error("Malformed repeat value.",1);

	printf("Repeat block %d\n",num);
	*/
	m = (macro*)malloc(sizeof(macro));
	if (!m) {
		error("Cannot allocate memory for repeat block.", 1);
	}
	m->name = (char*)malloc(13);
	if (!m->name) {
		error("Cannot allocate memory for repeat block.", 1);
	}
	strcpy(m->name, "repeat block");
	m->mlabels = NULL;
	m->times = 0;
	m->nxt = NULL;
	m->lines = NULL;
	m->num = num; /* num_cvt(str); */
	m->tp = 1;
	tail = NULL;

	while (1) {
		str = get_nxt_word(PARSE_NEXT_LINE);
		if (!str)
			error("Unterminated repeat statement", 1);

		if (!STRCASECMP(str, ".ENDR"))
			break;
		if (!STRCASECMP(str, ".REPT"))
			error("No nested repeat blocks.", 1);
		if ((!STRCASECMP(str, ".MACRO")) ||
			(!STRCASECMP(str, ".ENDM"))) {
			error("No macro definitions inside repeat blocks.", 1);
		}

		str = get_nxt_word(PARSE_CURRENT_LINE);  /* Retrieve entire line */
		get_nxt_word(PARSE_LINE_REST);      /* Reset line to force read */
		line = (macro_line*)malloc(sizeof(macro_line));
		if (!line) {
			error("Error allocting memory for repeat.", 1);
		}
		line->nxt = NULL;
		line->line = (char*)malloc(strlen(str) + 1);
		if (!line->line) {
			error("Error allocting memory for repeat.", 1);
		}
		strcpy(line->line, str);
		if (!m->lines)
			m->lines = tail = line;
		else {
			tail->nxt = line;
			tail = line;
		}
	}
	rept = (macro_call*)malloc(sizeof(macro_call));
	if (rept == NULL)
		error("Error allocting memory for repeat.", 1);
	rept->argc = 0;
	rept->orig = m;
	rept->cmd = NULL;
	rept->nxt = invoked;
	rept->line = m->lines;

	if ((m->num > 0) && (m->lines))
		invoked = rept;
	else {
		if (!pass) {
			if (!m->lines)
				error("Empty repeat block ignored.", 0);
			else
				error("Repeat block of 0 ignored.", 0);
		}
		del_rept(rept);
	}

	return 1;
}
/*=========================================================================*
 * function del_rept(macro *kill)
 *
 * this destroys a repeat macro
 *=========================================================================*/
int del_rept(macro_call* mkill) {
	macro* kill;
	macro_line* walk, * nxt;

	kill = mkill->orig;
	walk = kill->lines;
	while (walk) {
		nxt = walk->nxt;
		free(walk->line);
		free(walk);
		walk = nxt;
	}
	free(kill);
	free(mkill);

	return 0;
}

/*=========================================================================*
 * function clean_up
 *
 * this performs general clean-up after assembly
 *=========================================================================*/
void clean_up() {
	symbol* sym, * kill;
	macro* mac, * killm;
	macro_line* macl, * killml;
	int i;

	cleanUnk();
	sym = linkit();  /* Free symbol table entries... */
	while (sym) {
		if ((sym->tp != OPCODE) && (sym->tp != DIRECT)) {
			free(sym->name);
			free(sym->orig);
		}
		kill = sym;
		sym = sym->lnk;
		free(kill);
	}

	mac = macro_list;  /* Free macro definitions... */
	while (mac) {
		macl = mac->lines;
		while (macl) {
			free(macl->line);
			killml = macl;
			macl = macl->nxt;
			free(killml);
		}
		killm = mac;
		mac = mac->nxt;
		free(killm);
	}

	for (i = 0; i < ISIZE; i++) {  /* Free warning cache */
		ihashNode* walk, * kill;
		walk = ihash[i];
		while (walk) {
			kill = walk;
			walk = walk->nxt;
			free(kill);
		}
	}

	kill_banks();
	free(outline);

	free_str_list(includes);
	free_str_list(predefs);
}
/*=========================================================================*/

longJump* getLongJumpReference(char* fileInfo, int lineNumber)
{
	int i;
	longJump* walk;
	char* look;
	char nameIt[256];

	// Create a hash code of the source file-line
	sprintf(nameIt, "%s @ %d", fileInfo, lineNumber);

	look = nameIt;

	i = hashit(look);			// Find word index
	walk = ljHash[i];			// Get initial pointer
	while (walk) 
	{       
		// Search list for correct entry
		if (!strcmp(walk->name, look)) {
			return walk;
		}
		walk = walk->nxt;
	}
	// Not found, so create it
	longJump* info = malloc(sizeof(longJump));
	memset(info, 0, sizeof(longJump));
	info->name = STRDUP(nameIt);
	info->filename = STRDUP(fileInfo);
	info->lineNr = lineNumber;
	info->distance = 65535;		// Max jump distance

	walk = ljHash[i];
	if (!walk) {              /* First word at this location */
		ljHash[i] = info;
		return info;
	}
	while (walk->nxt)         /* Otherwise, traverse list to end */
		walk = walk->nxt;
	walk->nxt = walk->lnk = info;  /* and finally add word to list */

	return info;
}

/*==========================================================================*
 * procedure alpha_merge
 * Part of the merge sort function, this does the actual merge...
 * sorts list alphabetically.
 *==========================================================================*/
longJump* alpha_mergeLJ(longJump* p, longJump* q)
{
	longJump* r, * l;

	if ((strcmp(p->name, q->name) < 0)) {
		r = p;
		p = p->lnk;
	}
	else {
		r = q;
		q = q->lnk;
	}
	l = r;
	while ((p) && (q))
		if ((strcmp(p->name, q->name) < 0)) {
			r->lnk = p;
			r = p;
			p = p->lnk;
		}
		else {
			r->lnk = q;
			r = q;
			q = q->lnk;
		}
	if (!p)
		r->lnk = q;
	else
		r->lnk = p;
	return (l);
}

int printedHeader = 0;
void dumpHeader() {
	if (printedHeader)
		return;

	printedHeader = 1;
	fprintf(stderr, "\n\nPossible long jump optimizations\n================================\n");

}
void dumpLongJumpInfo(longJump* ref)
{
	if (ref->makeShort)
	{
		dumpHeader();
		fprintf(stderr, "%s\t", ref->name);
		if (ref->outLine1)
			fprintf(stderr, "%s --> %s ; distance is %d\n", ref->origLine, ref->outLine1, ref->distance);
	}
	else
	{
		// Long jump but might be a short one
		if (ref->distance >= -128 && ref->distance < 127)
		{
			// This could have been a short jump
			dumpHeader();
			fprintf(stderr, "%s\t%s --> %s\n", ref->name, ref->origLine, ref->altLine ? ref->altLine : "???");
			if (ref->outLine1)
				fprintf(stderr, "\tNow:\t%s ; distance is %d\n", ref->outLine1, ref->distance);
			if (ref->outLine2)
				fprintf(stderr, "\t\t%s\n", ref->outLine2);
		}
	}
}

void dumpLongJumpOptimizations()
{
	longJump* head, * walk;
	int i = 0;

	head = walk = NULL;
	while ((i < HSIZE) && (!ljHash[i]))
		i++;

	if (i == HSIZE)
		return;

	head = walk = ljHash[i];

	while (i < HSIZE) 
	{  
		// Walk through all indices of hash table
		while (walk->nxt) {
			walk->lnk = walk->nxt;
			walk = walk->nxt;
		}
		walk->lnk = NULL;
		i++;
		while ((i < HSIZE) && (!ljHash[i]))
			i++;
		if (i < HSIZE) {
			walk->lnk = ljHash[i];
			walk = ljHash[i];
		}
	}
	// walk from clist
	if (head == NULL)
		return;

	// Sort the names

	longJump* p, * q, * stack[128];
	int c, merge, d;

	p = head;
	c = 0;
	while (p) 
	{
		c++;
		i = c;
		merge = 0;
		while (!(i & 1)) {
			i /= 2;
			merge++;
		}
		q = p;
		p = p->lnk;
		q->lnk = NULL;
		for (i = 0; i <= merge - 1; i++) {
			q = alpha_mergeLJ(q, stack[i]);
		}
		stack[merge] = q;
	}
	merge = -1;
	while (c) {
		d = c & 1;
		c = c / 2;
		merge++;
		if (d) {
			if (p) {
				p = alpha_mergeLJ(p, stack[merge]);
			}
			else {
				p = stack[merge];
			}
		}
	}
	head = p;

	longJump* pos = head;
	while (pos) 
	{
		dumpLongJumpInfo(pos);
		pos = pos->lnk;
	}
}