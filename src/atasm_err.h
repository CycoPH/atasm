/*==========================================================================
 * Project: Atari cross-assembler
 * File: atasm_err.h
 *
 * Contains typedefs and prototypes for the assembler error handler
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
#ifndef ATASM_ERR_H
#define ATASM_ERR_H

#define ISIZE 128

typedef struct ihashNode {
  unsigned int id;
  unsigned int data;
  struct ihashNode *nxt;
} ihashNode;

typedef struct options {  /* structure to hold user preferences */
  int warn, obj;
  int savetp;
  int ill,verbose;
  int strict;
  int MAElocals;
  char *MAEname;
  unsigned char fillByte;
  int symbolDumpOptions;	/* 0 = no restriction, use ".opt [no] SYMDUMP" to turn this flag on or off */
  int showMemory;			// Output the memory layout of the code after compilation
  int evalOnly;				// 1 then NOTHING is written to the final output file
  int autoBankMode;			// 1 then every org (*=) is a new bank
} options;

extern options opt;
extern ihashNode *ihash[ISIZE];
extern int warn;

extern unsigned int err_crc32(const unsigned char *s, unsigned int len);
extern int error(char *errorMessage, int tp);
extern void message(char* msg);
extern void fatal_error(char* errorMessage);

extern char* replace(
	char const* const original,
	char const* const pattern,
	char const* const replacement
);

#endif
