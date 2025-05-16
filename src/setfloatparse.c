/*==========================================================================
 * Project: Atari cross-assembler
 * File: setparse.c
 *
 * Contains the routines to initialize expression parsing
 *==========================================================================
 * Created: 3/26/98 mws
 * Modifications:
 *                12/18/98 mws rewrote for full expression parsing
 *                03/03/03 mws added interpretation of #$LABEL
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
 *=========================================================================*/

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>     /* strtof */

#include "compat.h"
#include "symbol.h"

void fatal_error(char* errorMessage);
int error(char* errorMessage, int tp);
int floatparse();
extern float frval;
int fvnum;
float fnums[64];

extern int get_dotname(char* src, char* dst);
extern symbol* validate_symbol(char* str);

static char* parse_string;
/*=========================================================================*
  function floatlex()

  returns the next token in the expression stream to the parser
 *=========================================================================*/
int floatlex()
{
	char terminals[] = "[]-/*+-=#GLv";
	char* look, c;

	if (parse_string) {
		c = *parse_string;
		parse_string++;
	}
	else
		c = 0;

	look = strchr(terminals, c);
	if (!look) {
		fatal_error("Malformed expression");
		return 0;
	}
	else {
		return c;
	}
}
/*=========================================================================*
  function parse_float_expr(char *str)
  parameters: str - the expression to parse (numbers and directive only)

  Create simpler expression (replace .DIRECTIVEs, etc) and then return
  result.
 *=========================================================================*/
float parse_float_expr(char* a)
{
	int num;
	char expr[80], * look, * walk;

	fvnum = num = 0;
	look = a;
	walk = expr;
	while (*look) {
		if (ISDIGIT(*look)) {
			*walk++ = 'v';
			float result = strtof(look, &look);
			fnums[num] = result;
			num++;
		}
		else if ((*look == '<') && (*(look + 1) == '<')) {
			look += 2; *walk++ = 'Q';
		}
		else if ((*look == '>') && (*(look + 1) == '>')) {
			look += 2; *walk++ = 'W';
		}
		else if ((*look == '<') && (*(look + 1) == '>')) {
			look += 2; *walk++ = '#';
		}
		else if ((*look == '<') && (*(look + 1) == '=')) {
			look += 2; *walk++ = 'L';
		}
		else if ((*look == '>') && (*(look + 1) == '=')) {
			look += 2; *walk++ = 'G';
		}
		else *walk++ = *look++;
	}
	*walk = 0;
	parse_string = expr;

	if (floatparse()) {
		fatal_error("Malformed expression");
	}
	return frval;
}

/*=========================================================================*
  function get_float_expression(char *str, int tp)
  parameters: str - the expression to parse
			  tp  - flag error (1=yes, 0=return 0xffff)
  returns the value of the expression

  This function calculates the value of an expression, or generates an error
 *=========================================================================*/
float get_float_expression(char* str, int tp) 
{
	char buf[256], work[1024];
	char* look, * walk, * w;
	int v;
	symbol* sym;
	char math[] = "[]*/+-&|^<>=";

	buf[0] = 0;
	walk = buf;
	look = str;
	while (*look) {
		if (*look == '*') {
			if ((walk == buf) || ((!ISDIGIT(*(walk - 1))) && (*(walk - 1) != ']')) ||
				(*(look + 1) == '*')) {
				snprintf(work, 256, "%d", pc);
				strcpy(walk, work);
				walk += strlen(work);
				look++;
			}
			else *walk++ = *look++;
		}
		else if (strchr(math, *look))
			*walk++ = *look++;
		else if (*look == '!') {     /* Old binary OR operator */
			*walk++ = '|';
			look++;           /* skip to next char */
		}
		else if (ISDIGIT(*look)) {
			float result = strtof(look, &look);
			snprintf(work, 256, "%f", result);
			strcpy(walk, work);
			walk += strlen(work);
		}
		else if (*look == '$') {  /* Hex value */
			char* hold;
			w = work;
			*w++ = *look++;
			hold = look;

			while (ISXDIGIT(*look))
				*w++ = *look++;
			if (ISALPHA(*look)) {  /* symbol #$SOMETHING, give warning */
				v = get_name(hold, work);
				look = hold + v;
				sym = findsym(work);
				if (!sym) {
					fatal_error("Non-hex expression");
				}
				else {
					snprintf(buf, 256, "Interpreting '$%s' as hex value '$%x'", work, sym->addr);
					error(buf, 0);
				}
				v = sym->addr;
				sym->ref = 1;
				snprintf(work, 256, "$%x", v);
			}
			else
				*w = 0;
			v = num_cvt(work);
			snprintf(work, 256, "%d", v);
			strcpy(walk, work);
			walk += strlen(work);
		}
		else if (*look == '~') {  /* binary value */
			w = work;
			*w++ = *look++;
			while (ISDIGIT(*look))
				*w++ = *look++;
			*w = 0;
			v = num_cvt(work);
			snprintf(work, 256, "%d", v);
			strcpy(walk, work);
			walk += strlen(work);
		}
		else if (*look == '\'') { /* Character value */
			look++;
			v = *look;
			look++;
			if ((*look == '\'') && (v != ' ')) {
				error("Probably shouldn\'t be surrounded by \'", 0);
				look++;
			}
			snprintf(work, 256, "%d", v);
			strcpy(walk, work);
			walk += strlen(work);
		}
		else if (*look == '.') {
			if (!STRNCASECMP(look, ".NOT", 4)) {
				look += 4; *walk++ = 'N';
			}
			else {
				fatal_error("Invalid compiler directive in expression.");
			}
		}
		else if (*look == '(') {
			look++;
			*walk++ = '[';
		}
		else if (*look == ')') {
			look++;
			*walk++ = ']';
		}
		else {
			/* Try and get a name including . so DATA.CMD would be valid
			 * If there is a symbol hit on that symbol the we assume that its NOT a .some command
			 */
			v = get_dotname(look, work);
			sym = findsym(work);
			if (sym == NULL) {
				/* symbol was not found so retry with the non . method */
				v = get_name(look, work);
			}
			look += v;
			sym = validate_symbol(work);
			if ((!sym) && (tp)) {
				snprintf(buf, 256, "Unknown symbol '%s'", work);
				dump_symbols();
				fatal_error(buf);
			}
			if ((!sym) || ((sym->tp == MACROL) && (!sym->macroShadow))) {
				UnknownLabel* look;

				look = isUnknown(work);
				if (look) {
					if (look->zp)
						return 0xff;
				}
				else {
					addUnknown(work);
				}
				if (sym)  /* mws fix for overflow.m65 */
					return sym->addr;
				return 0xffff;
			}
			else {
				v = sym->addr;
				if (v > 32767)
				{
					// number is -ve
					v = -(65536 - v);
				}
				if ((pass) && (v == 0xffff) && (sym->ref != 1)) {
					double_fwd = 1;
				}
			}
			sym->ref = 1;

			snprintf(work, 256, "%f", (float)v);
			strcpy(walk, work);
			walk += strlen(work);
		}
	}
	*walk = 0;
	return parse_float_expr(buf);
}
/*=========================================================================*/
