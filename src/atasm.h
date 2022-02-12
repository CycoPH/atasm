/*==========================================================================
 * Project: atari cross assembler
 * File: atasm.h
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
#ifndef ATASM_H
#define ATASM_H

 /*==========================================================================*/
 /* Some defines for number format */
#define IS_DECIMAL 0
#define IS_HEX 1
#define IS_BINARY 2

/*==========================================================================*/
/* Processing modes when getting the next word/operand/etc to parse */
#define PARSE_NEXT_LINE 0		/* normal processing, getting next line */
#define PARSE_LINE_REST 1		/* get rest of current line */
#define PARSE_CURRENT_LINE 2	/* return entire current line */
#define PARSE_PEEK_LINE_REST 3	/* get rest of current line, but don't advance buffer (peeking ahead) */
#define PARSE_NEXT_WORD 4		/* get next word, returning "" when eol is hit (no advance to next line) */
#define PARSE_SKIP 5			/* 'skip' mode, don't subst macro params! */
#define PARSE_REPLACE_COMMAS 6	/* replace commas with spaces in reading buffer and return NULL */
#define PEEK_COMMENT 7			/* return the comment at the end of the line */

#endif

