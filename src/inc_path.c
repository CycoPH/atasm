/*==========================================================================
 * Project: ATasm: Atari cross-assembler
 * File: inc_path.c
 *
 * Provides a linked list store search directories for .INCLUDEd files.
 *==========================================================================
 * Created: 08/03/2002 B. Watson
 * Modifications:
 *  08/05/02 mws added comment blocks, reformatted slightly
 *  03/03/03 mws fopen include now tries to open natural path first, then
 *               explores includes
 *  07/27/03 mws rewrote to reduce number and size of mallocs
 *==========================================================================*
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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "symbol.h"
#include "inc_path.h"
#include "atasm_err.h"

/*=========================================================================*
  function free_str_list
  parameters: str - the head of the list to free

  This cleans up a string list
 *=========================================================================*/
void free_str_list(str_list *str) {
  str_list *kill, *walk=str;
  while(walk) {
    kill=walk;
    walk=walk->next;
    free(kill->str);
    free(kill);
  }
}

/*=========================================================================*
 * function init_include
 * parameters: none
 *
 * initializes search directory list;
 *=========================================================================*/
str_list *init_include() {
  str_list *head;

  head=(str_list*)malloc(sizeof(str_list));
  if (head==NULL)
      fatal_error("Cannot allocate memory to initialize include list");
  head->next = NULL;
  head->str = (char*)malloc(2);
  if (head->str==NULL)
      fatal_error("Cannot allocate memory to initialize include list");
  head->str[0]='.';
  head->str[1]=0;
  return head;
}

/*=========================================================================*
  function append_include
  parameters: head - the current list head;
              path - the path to append

  add another path to the include directory search path
 *=========================================================================*/
void append_include(str_list *head, char *path) {
  str_list *append, *walk=head;

  if ((!path)||(!(*path)))
    return;

  while(walk->next) {
    if (!strcmp(walk->str,path))
      return;
    walk=walk->next;
  }

  append=(str_list *)malloc(sizeof(str_list));
  if(!append)
      fatal_error("Cannot grow include list");
  append->str=(char*)malloc(strlen(path)+1);
  if (append->str == NULL)
      fatal_error("Cannot grow include list");
  strcpy(append->str, path);
  append->next=NULL;
  walk->next=append;
}

/*=========================================================================*
  function fopen_include
  parameters: head - the list to search
        fname - the file to open

  attempts to open a file, checking all include paths
 *=========================================================================*/
FILE *fopen_include(str_list *head, char *fname, int is_binary, char* store_fname_here, size_t store_fname_size) {
  char errbuf[255],mode[3];
  char *full_path;
  FILE *in;
  int n;

  if (is_binary)
    strcpy(mode,"rb");
  else
    strcpy(mode,"rt");

  /* First, attempt to open file normally... */
  in=fopen(fname,mode);
  if (in) {
    if (strlen(fname) + 1 > store_fname_size) {
      fclose(in);
      snprintf(errbuf, sizeof(errbuf), "Filename too long: '%s'", fname);
      fatal_error(errbuf);
    }
    memcpy(store_fname_here, fname, strlen(fname) + 1);
    return in;
  }
  /* Now test with include paths... */
  full_path = (char*)malloc(MAX_PATH);
  if(full_path==NULL)
      fatal_error("Cannot allocate MAX_PATH bytes in fopen_include");

  while(head) {
    n = snprintf(full_path, MAX_PATH, "%s%s%s", head->str, DIR_SEP, fname);
    if (n < 0 || n >= MAX_PATH) {
      /* Path too long for this include entry; skip it */
      head = head->next;
      continue;
    }
    in=fopen(full_path,mode);
    if (in) {
      if ((size_t)n + 1 > store_fname_size) {
        fclose(in);
        free(full_path);
        snprintf(errbuf, sizeof(errbuf), "Resolved include path too long: '%s'", full_path);
        fatal_error(errbuf);
      }
      memcpy(store_fname_here, full_path, (size_t)n + 1);
      free(full_path);
      return in;
    }
    head=head->next;
  }
  free(full_path);
  snprintf(errbuf,sizeof(errbuf),"Cannot open file: '%s'", fname);
  fatal_error(errbuf);
  return NULL;
}
/*=========================================================================*/






