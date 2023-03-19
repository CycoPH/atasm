/*==========================================================================
 * Project: atari cross assembler
 * File: symbol.h
 *
 * Contains typedefs and prototypes for the assembler
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
#ifndef SYMBOL_H
#define SYMBOL_H

#define MAJOR_VER 1
#define MINOR_VER 23
#define BETA_VER 0

 /*==========================================================================*/

#define DUMP_NOTHING        0
#define DUMP_CONSTANTS      1
#define DUMP_LABELS_ALL     2
#define DUMP_LABELS_PRIMARY 4
#define DUMP_MACROS         8       // Don't dump labels with the ? at the front

#define DUMP_ALL        (DUMP_CONSTANTS | DUMP_LABELS_PRIMARY | DUMP_MACROS)


/*==========================================================================*/
typedef struct file_tracking /* Track the filename */
{
	char* name;
	struct file_tracking* nxt;
} file_tracking;

/*==========================================================================*/
typedef struct memory_name /* Name of a memory region */
{
	int addr;               // Address of the memory region start
	char* name;             // Name given to this memory region
	struct memory_name* nxt;// ptr to next name
} memory_name;

/*==========================================================================*/
typedef struct memBank {
	int id, sym_id;
	unsigned char* memmap, * bitmap;  /* memory snapshot, and bitmap */
	int offset;
	struct memBank* nxt;
} memBank;
/*==========================================================================*/
typedef struct symbol {  /* Symbol table entry */
	char* name;
	char* orig;   /* original name, no ? processing yet */
	/* tp:
	   0: opcode
	   1: directive
	   2: user label
	   3: user transitory equate
	   4: macro
	   5: macro label/equate
	   6: equate
	   7: macro transitory label
	 */
	short tp;
	unsigned short addr;
	unsigned short bank;
	unsigned short ref;
	unsigned short num;
	char* macroShadow;
	struct symbol* nxt;
	struct symbol* lnk, * mlnk;
	/* Track the source of the symbol */
	int lineNr;
	struct file_tracking* ftrack;
	/* comment from source file*/
	char* comment;
	/* When dumping symbols we can prevent the symbol from showing up in the
	 * 'asm-symbols.json' file
	 * 0 = Include is the dump
	 * 1 = exclude from constant dump
	 */
	int dumpOptions;
} symbol;

/*==========================================================================*/
typedef struct unkLabel {
	char* label;
	int zp;
	struct unkLabel* nxt;
} unkLabel;
/*==========================================================================*/
typedef struct strList {
	char* str;
	struct strList* next;
} str_list;
/*==========================================================================*/
/* Some defines for symbol types -- see above comment */
#define OPCODE 0
#define DIRECT 1
#define LABEL  2
#define TEQUATE 3
#define MACRON 4
#define MACROL 5
#define EQUATE 6
#define MACROQ 7
/*==========================================================================*/
typedef struct file_stack { /* File process entry */
	char* name;
	FILE* in;
	int line;
	char** trackClear;
	struct file_stack* nxt;
	struct file_tracking* ftrack;
} file_stack;

/*==========================================================================*/
typedef struct macro_line { /* an entry in a macro */
	char* line;
	struct macro_line* nxt;
} macro_line;
/*==========================================================================*/
typedef struct macro {  /* a macro */
	char* name;           /* name */
	int tp, param, num;    /* number of parameters, # lines */
	short times;          /* number of invokations */
	macro_line* lines;    /* The actual text */
	symbol* mlabels;      /* assembled labels */
	struct macro* nxt;
} macro;
/*==========================================================================*/
typedef struct macro_call {
	int argc;             /* number of arguments passed to macro */
	macro* orig;          /* pointer to original macro */
	macro_line* cmd;      /* parameters */
	macro_line* line;     /* pointer to next macro line */
	struct macro_call* nxt;
} macro_call;

/*==========================================================================*
 * some symbols
 *==========================================================================*/
extern unsigned short pc;   /* program counter */
extern int pass; /* pass number */
extern int eq, verbose;  /* assignment flag, verbosity flag */
extern int local, warn, bsize;
extern int repass;  /* flag indicating that a referenced label changed size */
extern file_stack* fin;
extern macro* macro_list;
extern macro_call* invoked;
extern memBank* banks, * activeBank;
extern char* outline;  /* the line of text written out in verbose mode */
extern unkLabel* unkLabels; /* list of unknown, referenced symbols */

extern int double_fwd; /* flag indicating a double forward reference occured */

#define HSIZE 511
extern symbol* hash[HSIZE];
extern FILE* listFile;

/*==========================================================================*
 * Long jump functionality
 *==========================================================================*/
typedef struct longJump {  /* Symbol table entry */
	char* name;

	int type;				// What type of long jump JEQ (31), JNE, JPL, JMI, JCC, JCS, JVC, JVS (38)

	int pc;					// Where in memory is the instruction located
	int targetAddr;			// Where in memory is it jumping to
	char* targetName;		/// Which label are we jumping to
	int makeShort;			// 1 then make it a short jump
	int distance;			// how long is the jump

	char* origLine;			// Original source code Line
	char* outLine1;			// Generated assembler code
	char* outLine2;			// Generated assembler code
	char* altLine;			// Alternative line might be

	struct longJump* nxt;
	struct longJump* lnk, * mlnk;

	/* Track the source of the long jump */
	int lineNr;
	char* filename;
} longJump;

extern longJump* ljHash[HSIZE];

/*==========================================================================*
 * some prototypes
 *==========================================================================*/
char* get_nxt_word(int tp);
int squeeze_str(char* str);
int num_cvt(char* num);

unsigned short get_expression(char* str, int tp);
int get_signed_expression(char* str, int tp);
int get_name(char* src, char* dst);

symbol* findsym(char* name);
int addsym(symbol* wrd);
void remsym(symbol* wrd);
symbol* get_sym();
int dump_symbols();
int dump_labels(char* fname);
int dump_c_header(char* header_fname, char* asm_fname);
int dump_assembler_header(char* header_fname);
void dump_VSCode(file_tracking* trackedFiles, int partsToDump);
macro_call* get_macro_call(char* name);
int macro_subst(char* name, char* in, macro_line* cmd, int max);
int create_macro(symbol* sym);
int macro_param(macro_call* mc, char* cmd);
int skip_macro();
int clear_ref();
int do_rept(symbol* sym);
int del_rept(macro_call* kill);

void cleanUnk();
void fixRepass();
int find_extension(char* name);

int save_state(char* fin, char* fout);
int save_snapshot(char* fin, char* fout);

int write_xfd_file(char* image, char* file);
void process_predef(str_list* def);

void clean_up();

void addUnk(char* unk);
unkLabel* isUnk(char* unk);
void defUnk(char* unk, unsigned short addr);

int clear_banks();
void kill_banks();

longJump* getLongJumpReference(char* fileInfo, int lineNumber);
void dumpLongJumpOptimizations();

#endif
