/*==========================================================================
 * Project: atari cross assembler
 * File: setparse.c
 *
 * Contains the routines to intilize expression parsing
 *==========================================================================
 * Created: 3/26/98 mws
 * Modifications:
 *                12/18/98 mws rewrote for full expression parsing
 *==========================================================================*/
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "symbol.h"

int error(char *err, int tp);
int yyparse();
extern short rval;
short vnum, nums[64];

char *parse_string;
/*=========================================================================*
  function yylex()

  returns the next token in the expression stream to the parser
 *=========================================================================*/
int yylex()
{
  char terminals[]="[]<>-N/*+-&|^=#GLAOv";
  char *look,c;

  if (parse_string) {
    c=*parse_string;
    parse_string++;
  } else
    c=0;
  
  look=strchr(terminals,c);
  if (!look) {
    error("Malformed expression",1);
    return 0;
  } else {
    return c;
  }
}
/*=========================================================================*
  function parse_expr(char *str)
  parameters: str - the expression to parse (numbers and directive only)
  
  Create simpler expression (replace .DIRECTIVEs, etc) and then return
  retult.
 *=========================================================================*/
int parse_expr(char *a) {
  int v,num;
  char expr[80], *look, *walk, *n;
  
  vnum=num=0;
  look=a;
  walk=expr;
  while(*look) {
    if (isdigit(*look)) {
      *walk++='v';
      n=walk;
      while(isdigit(*look))
	*n++=*look++;
      *n=0;
      sscanf(walk,"%d",&v);
      nums[num]=v;
      num++;
    } else if (*look=='<')&&(*(look+1)=='>') {
      *look++; *look++; *walk++='#';
    } else if (*look=='<')&&(*(look+1)=='=') {
      *look++; *look++; *walk++='L';
    } else if (*look=='>')&&(*(look+1)=='=') {
      *look++; *look++; *walk++='G';
    } else *walk++=*look++;
  }
  *walk=0;
  parse_string=expr;
  
  if (yyparse()) {
    error("Malformed expression",1);
  } 
  return rval;
}
/*=========================================================================*
  function get_name(char *src, char *dst)
  parameters: src - pointer to source string
              dst - pointer to destination string

  This copies an alphanumeric string from src to dst, stopping when either
  an illegal character is found, or the string terminates.  The name is
  capitalized as it is copied
 *=========================================================================*/
int get_name(char *src, char *dst) {
  int l=0;
  
  while((isalnum(*src))||(*src=='_')||((!l)&&((*src=='?')||(*src=='@')))) {
    *dst++=toupper(*src++);
    l++;
  }
  *dst=0;
  return l;
}
/*=========================================================================*
  function get_expression(char *str, int tp)
  parameters: str - the expression to parse
              tp  - ??
  returns the value of the expression
	      
  This function calculates the value of an expression, or generates an error
 *=========================================================================*/
short get_expression(char *str, int tp) {
  char buf[256], work[80];
  char *look, *walk, *w, c;
  int v,i;
  symbol *sym;
  char math[]="[]*/+-&|^<>=";

  walk=buf;
  look=str;
  while(*look) {
    if (*look=='*') {
      if ((walk==buf)||(!isdigit(*(walk-1)))||(*(look+1)=='*')) {
	sprintf(work,"%d",pc);
	strcpy(walk,work);
	walk+=strlen(work);
	look++;
      } else *walk++=*look++;
    } else if (strchr(math,*look))
      *walk++=*look++;
    else if (isdigit(*look)) {
      while(isdigit(*look)) { /* Immediate value */
	*walk++=*look++;
      }
    } else if (*look=='$') {  /* Hex value */
      w=work;
      *w++=*look++;
      while(isxdigit(*look))
	*w++=*look++;
      *w=0;
      v=num_cvt(work);
      sprintf(work,"%d",v);
      strcpy(walk,work);
      walk+=strlen(work);
    } else if (*look=='~') {  /* binary value */
      w=work;
      *w++=*look++;
      while(isdigit(*look))
	*w++=*look++;
      *w=0;
      v=num_cvt(work);
      sprintf(work,"%d",v);
      strcpy(walk,work);
      walk+=strlen(work);
    } else if (*look=='\'') { /* Character value */
      look++;
      v=*look;
      look++;
      if (*look=='\'')
	error("Probably shouldn\'t be surrounded by \'",0);
      sprintf(work,"%d",v);
      strcpy(walk,work);
      walk+=strlen(work);
    } else if (*look=='.') {
      if (!strncmp(look,".NOT",4)) {
	look+=4; *walk++='N';
      } else if (!strncmp(look,".AND",4)) {
	look+=4; *walk++='A';
      } else if (!strncmp(look,".OR",3)) {
	look+=3; *walk++='O';
      } else if (!strncmp(look,".DEF",4)) {
	look+=4;
	v=get_name(look,work);
	look+=v;
	sym=findsym(work);
	if (!sym) 
	  *walk++='0';
	else
	  *walk++='1';
      } else if (!strncmp(look,".REF",4)) {
	look+=4;
	v=get_name(look,work);
	look+=v;
	sym=findsym(work);
	if (!sym) 
	  *walk++='0';
	else {
	  if (sym->ref)
	    *walk++='1';
	  else
	    *walk++='0';
	}
      }
    } else if (*look=='(') {
      look++;
      *walk++='[';
    } else if (*look==')') {
      look++;
      *walk++=']';
    } else {
      v=get_name(look,work);
      look+=v;
      sym=findsym(work);
      if ((!sym)&&(tp)) {
	sprintf(buf,"Unknown symbol '%s'",work);
	dump_symbols();
	error(buf,1);
      }
      if (sym) {
	v=sym->addr;
      } else return 0xffff;      
      sprintf(work,"%d",v);
      strcpy(walk,work);
      walk+=strlen(work);
    }
  }
  *walk=0;

  v=parse_expr(buf);
  return (short)v;
}
/*=========================================================================*/
int main() {
  char buf[256];
  int i;
  
  while(!feof(stdin)) {
    fscanf(stdin,"%s",buf);
    if (!feof(stdin)) {
      i=parse_expr(buf);
      printf("=%d\n",i);
    }
  }
  return 1;
}
