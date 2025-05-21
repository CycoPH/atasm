/*==========================================================================
 * Project: Atari cross-assembler
 * File: atasm_err.c
 *
 * Contains error handler
 *==========================================================================
 * Created: 07/27/03 mws
 * Modifications:
 *
 *==========================================================================
 * TODO: Add vprintf-like error function for convenience...
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "atasm_err.h"

#include "compat.h"
#include "symbol.h"

#define ISIZE 128
ihashNode* ihash[ISIZE];


char* replace(
	char const* const original,
	char const* const pattern,
	char const* const replacement
) {
	size_t const replen = strlen(replacement);
	size_t const patlen = strlen(pattern);
	size_t const orilen = strlen(original);

	size_t patcnt = 0;
	const char* oriptr;
	const char* patloc;

	// find how many times the pattern occurs in the original string
	for (oriptr = original; (patloc = strstr(oriptr, pattern)); oriptr = patloc + patlen)
	{
		patcnt++;
	}

	// allocate memory for the new string
	size_t const retlen = orilen + patcnt * (replen - patlen);
	char* const returned = (char*)malloc(sizeof(char) * (retlen + 1));

	if (returned != NULL)
	{
		// copy the original string, 
		// replacing all the instances of the pattern
		char* retptr = returned;
		for (oriptr = original; (patloc = strstr(oriptr, pattern)); oriptr = patloc + patlen)
		{
			size_t const skplen = patloc - oriptr;
			// copy the section until the occurence of the pattern
			strncpy(retptr, oriptr, skplen);
			retptr += skplen;
			// copy the replacement 
			strcpy(retptr, replacement);
			retptr += replen;
		}
		// copy the rest of the string.
		strcpy(retptr, oriptr);
	}
	return returned;
}

/*=========================================================================*
 * Function: errAdd, add an item to the warning table
 * Parameters: id, the key; d, the data item to add
 * Returns: bool indicating success
 *=========================================================================*/
void errAdd(unsigned int id, unsigned int num) {
	ihashNode* in;
	unsigned int key = id;
	key += ~(key << 15);
	key ^= (key >> 10);
	key += (key << 3);
	key ^= (key >> 6);
	key += ~(key << 11);
	key ^= (key >> 16);
	key = key % ISIZE;

	in = (ihashNode*)malloc(sizeof(ihashNode));
	if (!in) {
		fatal_error("Out of memory creating warning table");
	}
	in->id = id;
	in->data = num;
	in->nxt = NULL;
	if (ihash[key]) {
		ihashNode* walk = ihash[key];
		while (walk->nxt) {
			walk = walk->nxt;
		}
		walk->nxt = in;
	}
	else {
		ihash[key] = in;
	}
}

/*=========================================================================*
 * Function: Get, retrieve an object from the table by UID
 * Parameters: id, the object id to return
 * Returns: the object, or NULL if not found
 *=========================================================================*/
int errCheck(unsigned int id, unsigned int num) {
	ihashNode* look;

	unsigned int key = id;
	key += ~(key << 15);
	key ^= (key >> 10);
	key += (key << 3);
	key ^= (key >> 6);
	key += ~(key << 11);
	key ^= (key >> 16);
	key = key % ISIZE;

	if (!ihash[key])
		return 0;
	look = ihash[key];
	while (look) {
		if ((look->id == id) && (look->data == num))
			return 1;
		look = look->nxt;
	}
	return 0;
}

void fatal_error(char* errorMessage)
{
	error(errorMessage, 1);
	exit(1);
}

char *InjectPC(const char* msg)
{
	// Look for {*} in the error message and replace it with the current PC
	if (strstr(msg, "{{*}}")) {
		char PC[20];
		sprintf(PC, "$%04x", pc);
		return replace(msg, "{{*}}", PC);
	}
	return NULL;
}

void message(char *msg)
{
	char* filename = "UNKNOWN";
	int lineNumber = 0;
	char macroMsg[256];
	macroMsg[0] = 0;

	char* processedErrorMsg = InjectPC(msg);

	if (fin)
	{
		char buf[256];

		snprintf(buf, 256, "%s%d%s", fin->name, fin->line, processedErrorMsg ? processedErrorMsg : msg);
		unsigned int crc = err_crc32((unsigned char*)buf, (int)strlen(buf));
		if (errCheck(crc, fin->line))
		{
			if (processedErrorMsg)
				free(processedErrorMsg);
			return;
		}
		else
			errAdd(crc, fin->line);

		filename = fin->name;
		lineNumber = fin->line;

		if (invoked)
			sprintf(macroMsg, "--[while expanding macro '%.200s']", invoked->orig->name);
	}
	fprintf(stderr, "\n %s: %s:%d: %s%s\n",
		"Message",
		filename, lineNumber,
		processedErrorMsg ? processedErrorMsg : msg,
		macroMsg
	);

	if (processedErrorMsg)
		free(processedErrorMsg);

	return;
}

/*=========================================================================*
 * function error(char *errorMessage, int errLevel)
 * parameters: errorMessage - the error message
 *             errLevel  - the error severity (0=warning, else fatal error)
 *
 * generates an error/warning message to stderr, including the position
 * of the error
 *=========================================================================*/
int error(char* errorMessage, int errLevel)
{
	char* filename = "UNKNOWN";
	int lineNumber = 0;
	char macroMsg[256];
	macroMsg[0] = 0;

	char* processedErrorMsg = InjectPC(errorMessage);

	if (opt.warn == 0 && errLevel == 0) {
		// Suppress warnings, if option no warn set
		warn++;
		return 1;
	}
	if (fin)
	{
		char buf[256];

		snprintf(buf, 256, "%s%d%s", fin->name, fin->line, processedErrorMsg ? processedErrorMsg : errorMessage);
		unsigned int crc = err_crc32((unsigned char*)buf, (int)strlen(buf));
		if (errCheck(crc, fin->line))
		{
			if (processedErrorMsg)
				free(processedErrorMsg);
			return 1;
		}
		else
			errAdd(crc, fin->line);

		filename = fin->name;
		lineNumber = fin->line;

		if (invoked)
			sprintf(macroMsg, "--[while expanding macro '%.200s']", invoked->orig->name);

		//fprintf(stderr, "\nIn %s\n ", fin->name);
		/*if (!invoked)
			fprintf(stderr, "\nIn %s, line %d--\n ", fin->name, fin->line);
		else
			fprintf(stderr, "\nIn %s, line %d--[while expanding macro '%s']\n ", fin->name, fin->line, invoked->orig->name);
		*/
	}
	fprintf(stderr, "\n %s: %s:%d: %s%s\n",
		errLevel ? "Error" : "Warning",
		filename, lineNumber,
		processedErrorMsg ? processedErrorMsg : errorMessage,
		macroMsg
	);

	if (processedErrorMsg)
		free(processedErrorMsg);

	if (errLevel)
	{
		// Exit on error
		if (listFile)
			fclose(listFile);
		exit(errLevel);
	}
	warn++;
	return 0;
}

/*=========================================================================*/
void floaterror(char* err)
{
	error(err, 1);
	exit(1);
}