int yylex();
void error (char *s,int tp);
extern int nums[];
extern int vnum;
int rval;

typedef long unsigned int size_t;
typedef __builtin_va_list __gnuc_va_list;
typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;
typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;
typedef __int8_t __int_least8_t;
typedef __uint8_t __uint_least8_t;
typedef __int16_t __int_least16_t;
typedef __uint16_t __uint_least16_t;
typedef __int32_t __int_least32_t;
typedef __uint32_t __uint_least32_t;
typedef __int64_t __int_least64_t;
typedef __uint64_t __uint_least64_t;
typedef long int __quad_t;
typedef unsigned long int __u_quad_t;
typedef long int __intmax_t;
typedef unsigned long int __uintmax_t;
typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct { int __val[2]; } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;
typedef int __daddr_t;
typedef int __key_t;
typedef int __clockid_t;
typedef void * __timer_t;
typedef long int __blksize_t;
typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;
typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;
typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;
typedef long int __fsword_t;
typedef long int __ssize_t;
typedef long int __syscall_slong_t;
typedef unsigned long int __syscall_ulong_t;
typedef __off64_t __loff_t;
typedef char *__caddr_t;
typedef long int __intptr_t;
typedef unsigned int __socklen_t;
typedef int __sig_atomic_t;
typedef struct
{
  int __count;
  union
  {
    unsigned int __wch;
    char __wchb[4];
  } __value;
} __mbstate_t;
typedef struct _G_fpos_t
{
  __off_t __pos;
  __mbstate_t __state;
} __fpos_t;
typedef struct _G_fpos64_t
{
  __off64_t __pos;
  __mbstate_t __state;
} __fpos64_t;
struct _IO_FILE;
typedef struct _IO_FILE __FILE;
struct _IO_FILE;
typedef struct _IO_FILE FILE;
struct _IO_FILE;
struct _IO_marker;
struct _IO_codecvt;
struct _IO_wide_data;
typedef void _IO_lock_t;
struct _IO_FILE
{
  int _flags;
  char *_IO_read_ptr;
  char *_IO_read_end;
  char *_IO_read_base;
  char *_IO_write_base;
  char *_IO_write_ptr;
  char *_IO_write_end;
  char *_IO_buf_base;
  char *_IO_buf_end;
  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;
  struct _IO_marker *_markers;
  struct _IO_FILE *_chain;
  int _fileno;
  int _flags2;
  __off_t _old_offset;
  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];
  _IO_lock_t *_lock;
  __off64_t _offset;
  struct _IO_codecvt *_codecvt;
  struct _IO_wide_data *_wide_data;
  struct _IO_FILE *_freeres_list;
  void *_freeres_buf;
  size_t __pad5;
  int _mode;
  char _unused2[15 * sizeof (int) - 4 * sizeof (void *) - sizeof (size_t)];
};
typedef __gnuc_va_list va_list;
typedef __off_t off_t;
typedef __ssize_t ssize_t;
typedef __fpos_t fpos_t;
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;
extern int remove (const char *__filename) __attribute__ ((__nothrow__ , __leaf__));
extern int rename (const char *__old, const char *__new) __attribute__ ((__nothrow__ , __leaf__));
extern int renameat (int __oldfd, const char *__old, int __newfd,
       const char *__new) __attribute__ ((__nothrow__ , __leaf__));
extern FILE *tmpfile (void) ;
extern char *tmpnam (char *__s) __attribute__ ((__nothrow__ , __leaf__)) ;
extern char *tmpnam_r (char *__s) __attribute__ ((__nothrow__ , __leaf__)) ;
extern char *tempnam (const char *__dir, const char *__pfx)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;
extern int fclose (FILE *__stream);
extern int fflush (FILE *__stream);
extern int fflush_unlocked (FILE *__stream);
extern FILE *fopen (const char *__restrict __filename,
      const char *__restrict __modes) ;
extern FILE *freopen (const char *__restrict __filename,
        const char *__restrict __modes,
        FILE *__restrict __stream) ;
extern FILE *fdopen (int __fd, const char *__modes) __attribute__ ((__nothrow__ , __leaf__)) ;
extern FILE *fmemopen (void *__s, size_t __len, const char *__modes)
  __attribute__ ((__nothrow__ , __leaf__)) ;
extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc) __attribute__ ((__nothrow__ , __leaf__)) ;
extern void setbuf (FILE *__restrict __stream, char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));
extern int setvbuf (FILE *__restrict __stream, char *__restrict __buf,
      int __modes, size_t __n) __attribute__ ((__nothrow__ , __leaf__));
extern void setbuffer (FILE *__restrict __stream, char *__restrict __buf,
         size_t __size) __attribute__ ((__nothrow__ , __leaf__));
extern void setlinebuf (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
extern int fprintf (FILE *__restrict __stream,
      const char *__restrict __format, ...);
extern int printf (const char *__restrict __format, ...);
extern int sprintf (char *__restrict __s,
      const char *__restrict __format, ...) __attribute__ ((__nothrow__));
extern int vfprintf (FILE *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg);
extern int vprintf (const char *__restrict __format, __gnuc_va_list __arg);
extern int vsprintf (char *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg) __attribute__ ((__nothrow__));
extern int snprintf (char *__restrict __s, size_t __maxlen,
       const char *__restrict __format, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 4)));
extern int vsnprintf (char *__restrict __s, size_t __maxlen,
        const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 0)));
extern int vdprintf (int __fd, const char *__restrict __fmt,
       __gnuc_va_list __arg)
     __attribute__ ((__format__ (__printf__, 2, 0)));
extern int dprintf (int __fd, const char *__restrict __fmt, ...)
     __attribute__ ((__format__ (__printf__, 2, 3)));
extern int fscanf (FILE *__restrict __stream,
     const char *__restrict __format, ...) ;
extern int scanf (const char *__restrict __format, ...) ;
extern int sscanf (const char *__restrict __s,
     const char *__restrict __format, ...) __attribute__ ((__nothrow__ , __leaf__));
extern int fscanf (FILE *__restrict __stream, const char *__restrict __format, ...) __asm__ ("" "__isoc99_fscanf") ;
extern int scanf (const char *__restrict __format, ...) __asm__ ("" "__isoc99_scanf") ;
extern int sscanf (const char *__restrict __s, const char *__restrict __format, ...) __asm__ ("" "__isoc99_sscanf") __attribute__ ((__nothrow__ , __leaf__));
extern int vfscanf (FILE *__restrict __s, const char *__restrict __format,
      __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 2, 0))) ;
extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 1, 0))) ;
extern int vsscanf (const char *__restrict __s,
      const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__format__ (__scanf__, 2, 0)));
extern int vfscanf (FILE *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vfscanf")
     __attribute__ ((__format__ (__scanf__, 2, 0))) ;
extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vscanf")
     __attribute__ ((__format__ (__scanf__, 1, 0))) ;
extern int vsscanf (const char *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vsscanf") __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__format__ (__scanf__, 2, 0)));
extern int fgetc (FILE *__stream);
extern int getc (FILE *__stream);
extern int getchar (void);
extern int getc_unlocked (FILE *__stream);
extern int getchar_unlocked (void);
extern int fgetc_unlocked (FILE *__stream);
extern int fputc (int __c, FILE *__stream);
extern int putc (int __c, FILE *__stream);
extern int putchar (int __c);
extern int fputc_unlocked (int __c, FILE *__stream);
extern int putc_unlocked (int __c, FILE *__stream);
extern int putchar_unlocked (int __c);
extern int getw (FILE *__stream);
extern int putw (int __w, FILE *__stream);
extern char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
     ;
extern __ssize_t __getdelim (char **__restrict __lineptr,
                             size_t *__restrict __n, int __delimiter,
                             FILE *__restrict __stream) ;
extern __ssize_t getdelim (char **__restrict __lineptr,
                           size_t *__restrict __n, int __delimiter,
                           FILE *__restrict __stream) ;
extern __ssize_t getline (char **__restrict __lineptr,
                          size_t *__restrict __n,
                          FILE *__restrict __stream) ;
extern int fputs (const char *__restrict __s, FILE *__restrict __stream);
extern int puts (const char *__s);
extern int ungetc (int __c, FILE *__stream);
extern size_t fread (void *__restrict __ptr, size_t __size,
       size_t __n, FILE *__restrict __stream) ;
extern size_t fwrite (const void *__restrict __ptr, size_t __size,
        size_t __n, FILE *__restrict __s);
extern size_t fread_unlocked (void *__restrict __ptr, size_t __size,
         size_t __n, FILE *__restrict __stream) ;
extern size_t fwrite_unlocked (const void *__restrict __ptr, size_t __size,
          size_t __n, FILE *__restrict __stream);
extern int fseek (FILE *__stream, long int __off, int __whence);
extern long int ftell (FILE *__stream) ;
extern void rewind (FILE *__stream);
extern int fseeko (FILE *__stream, __off_t __off, int __whence);
extern __off_t ftello (FILE *__stream) ;
extern int fgetpos (FILE *__restrict __stream, fpos_t *__restrict __pos);
extern int fsetpos (FILE *__stream, const fpos_t *__pos);
extern void clearerr (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
extern int feof (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int ferror (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern void clearerr_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
extern int feof_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int ferror_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern void perror (const char *__s);
extern int sys_nerr;
extern const char *const sys_errlist[];
extern int fileno (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int fileno_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern FILE *popen (const char *__command, const char *__modes) ;
extern int pclose (FILE *__stream);
extern char *ctermid (char *__s) __attribute__ ((__nothrow__ , __leaf__));
extern void flockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
extern int ftrylockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern void funlockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
extern int __uflow (FILE *);
extern int __overflow (FILE *, int);

static const char yytranslate[] = { 0,
     2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
     2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
     2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
     2, 2, 22, 2, 6, 2, 2, 11, 2, 2,
     2, 18, 16, 2, 17, 2, 19, 2, 2, 2,
     2, 2, 2, 2, 2, 2, 2, 2, 2, 7,
     5, 8, 2, 2, 4, 2, 2, 24, 2, 2,
     9, 2, 2, 2, 2, 10, 20, 21, 3, 2,
    14, 23, 2, 2, 2, 2, 15, 2, 2, 2,
    26, 2, 27, 13, 2, 2, 2, 2, 2, 2,
     2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
     2, 2, 2, 2, 2, 2, 2, 25, 2, 2,
     2, 2, 2, 12, 2, 2, 2, 2, 2, 2,
     2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
     2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
     2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
     2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
     2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
     2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
     2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
     2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
     2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
     2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
     2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
     2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
     2, 2, 2, 2, 2, 1, 2
};
static const short yyr1[] = { 0,
    28, 29, 29, 29, 29, 29, 29, 29, 29, 29,
    29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
    29, 29, 29, 29, 29
};
static const short yyr2[] = { 0,
     1, 1, 2, 2, 2, 2, 3, 3, 3, 3,
     3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
     3, 3, 3, 3, 3
};
static const short yydefact[] = { 0,
     0, 0, 0, 0, 2, 0, 1, 5, 4, 6,
     3, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    25, 24, 23, 21, 22, 17, 18, 20, 19, 8,
     7, 9, 10, 11, 12, 13, 15, 16, 14, 0,
     0, 0
};
static const short yydefgoto[] = { 50,
     7
};
static const short yypact[] = { 41,
    41, 41, 41, 41,-32768, 41, 65,-32768,-32768,-32768,
-32768, 27, 41, 41, 41, 41, 41, 41, 41, 41,
    41, 41, 41, 41, 41, 41, 41, 41, 41, 41,
-32768, 82, 98, 108, 108, 108, 108, 108, 108, 115,
   115, 115, -10, -10, 32, 32,-32768,-32768,-32768, 4,
    11,-32768
};
static const short yypgoto[] = {-32768,
    -1
};
static const short yytable[] = { 8,
     9, 10, 11, 51, 12, 26, 27, 28, 29, 30,
    52, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 13,
    14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
    24, 25, 26, 27, 28, 29, 30, 1, 2, 28,
    29, 30, 0, 31, 0, 0, 0, 3, 0, 0,
     0, 4, 0, 0, 0, 5, 6, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
    26, 27, 28, 29, 30, 14, 15, 16, 17, 18,
    19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
    29, 30, 15, 16, 17, 18, 19, 20, 21, 22,
    23, 24, 25, 26, 27, 28, 29, 30, 21, 22,
    23, 24, 25, 26, 27, 28, 29, 30, 24, 25,
    26, 27, 28, 29, 30
};
static const short yycheck[] = { 1,
     2, 3, 4, 0, 6, 16, 17, 18, 19, 20,
     0, 13, 14, 15, 16, 17, 18, 19, 20, 21,
    22, 23, 24, 25, 26, 27, 28, 29, 30, 3,
     4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
    14, 15, 16, 17, 18, 19, 20, 7, 8, 18,
    19, 20, -1, 27, -1, -1, -1, 17, -1, -1,
    -1, 21, -1, -1, -1, 25, 26, 3, 4, 5,
     6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 4, 5, 6, 7, 8,
     9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
    19, 20, 5, 6, 7, 8, 9, 10, 11, 12,
    13, 14, 15, 16, 17, 18, 19, 20, 11, 12,
    13, 14, 15, 16, 17, 18, 19, 20, 14, 15,
    16, 17, 18, 19, 20
};
int yychar;
int yylval;
int yynerrs;
int yyparse (void);
int
yyparse()
    
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register int *yyvsp;
  int yyerrstatus;
  int yychar1 = 0;
  short yyssa[200];
  int yyvsa[200];
  short *yyss = yyssa;
  int *yyvs = yyvsa;
  int yystacksize = 200;
  int yyval;
  int yylen;
  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = -2;
  yyssp = yyss - 1;
  yyvsp = yyvs;
yynewstate:
  *++yyssp = yystate;
  if (yyssp >= yyss + yystacksize - 1)
    {
      int *yyvs1 = yyvs;
      short *yyss1 = yyss;
      int size = yyssp - yyss + 1;
      if (yystacksize >= 10000)
 {
   yyerror("parser stack overflow");
   return 2;
 }
      yystacksize *= 2;
      if (yystacksize > 10000)
 yystacksize = 10000;
      yyss = (short *) __builtin_alloca (yystacksize * sizeof (*yyssp));
      __builtin_memcpy((char *)yyss,(char *)yyss1,size * sizeof (*yyssp));
      yyvs = (int *) __builtin_alloca (yystacksize * sizeof (*yyvsp));
      __builtin_memcpy((char *)yyvs,(char *)yyvs1,size * sizeof (*yyvsp));
      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
      if (yyssp >= yyss + yystacksize - 1)
 return(1);
    }
  goto yybackup;
 yybackup:
  yyn = yypact[yystate];
  if (yyn == -32768)
    goto yydefault;
  if (yychar == -2)
    {
      yychar = yylex();
    }
  if (yychar <= 0)
    {
      yychar1 = 0;
      yychar = 0;
    }
  else
    {
      yychar1 = ((unsigned)(yychar) <= 257 ? yytranslate[yychar] : 30);
    }
  yyn += yychar1;
  if (yyn < 0 || yyn > 135 || yycheck[yyn] != yychar1)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == -32768)
 goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;
  if (yyn == 52)
    return(0);
  if (yychar != 0)
    yychar = -2;
  *++yyvsp = yylval;
  if (yyerrstatus) yyerrstatus--;
  yystate = yyn;
  goto yynewstate;
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen];
  switch (yyn) {
case 1:
{ rval=yyvsp[0]; ;
    break;}
case 2:
{yyval=nums[vnum++]; ;
    break;}
case 3:
{yyval=!yyvsp[0]; ;
    break;}
case 4:
{yyval=((yyvsp[0])>>8)&0xff; ;
    break;}
case 5:
{yyval=(yyvsp[0])&0xff; ;
    break;}
case 6:
{yyval=-(yyvsp[0]); ;
    break;}
case 7:
{yyval=yyvsp[-2]|yyvsp[0]; ;
    break;}
case 8:
{yyval=yyvsp[-2]&yyvsp[0]; ;
    break;}
case 9:
{yyval=yyvsp[-2]^yyvsp[0]; ;
    break;}
case 10:
{yyval=yyvsp[-2]<<yyvsp[0]; ;
    break;}
case 11:
{yyval=yyvsp[-2]>>yyvsp[0]; ;
    break;}
case 12:
{yyval=yyvsp[-2]+yyvsp[0]; ;
    break;}
case 13:
{yyval=yyvsp[-2]-yyvsp[0]; ;
    break;}
case 14:
{yyval=yyvsp[-2]%yyvsp[0]; ;
    break;}
case 15:
{yyval=yyvsp[-2]*yyvsp[0]; ;
    break;}
case 16:
{yyval=yyvsp[-2]/yyvsp[0]; ;
    break;}
case 17:
{yyval=(yyvsp[-2]<yyvsp[0]); ;
    break;}
case 18:
{yyval=(yyvsp[-2]>yyvsp[0]); ;
    break;}
case 19:
{yyval=(yyvsp[-2]<=yyvsp[0]); ;
    break;}
case 20:
{yyval=(yyvsp[-2]>=yyvsp[0]); ;
    break;}
case 21:
{yyval=(yyvsp[-2]==yyvsp[0]); ;
    break;}
case 22:
{yyval=(yyvsp[-2]!=yyvsp[0]); ;
    break;}
case 23:
{yyval=(yyvsp[-2]&&yyvsp[0]); ;
    break;}
case 24:
{yyval=(yyvsp[-2]||yyvsp[0]); ;
    break;}
case 25:
{yyval=yyvsp[-1];;
    break;}
}
  yyvsp -= yylen;
  yyssp -= yylen;
  *++yyvsp = yyval;
  yyn = yyr1[yyn];
  yystate = yypgoto[yyn - 28] + *yyssp;
  if (yystate >= 0 && yystate <= 135 && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - 28];
  goto yynewstate;
yyerrlab:
  if (! yyerrstatus)
    {
      ++yynerrs;
 yyerror("parse error");
    }
  goto yyerrlab1;
yyerrlab1:
  if (yyerrstatus == 3)
    {
      if (yychar == 0)
 return(1);
      yychar = -2;
    }
  yyerrstatus = 3;
  goto yyerrhandle;
yyerrdefault:
yyerrpop:
  if (yyssp == yyss) return(1);
  yyvsp--;
  yystate = *--yyssp;
yyerrhandle:
  yyn = yypact[yystate];
  if (yyn == -32768)
    goto yyerrdefault;
  yyn += 1;
  if (yyn < 0 || yyn > 135 || yycheck[yyn] != 1)
    goto yyerrdefault;
  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == -32768)
 goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;
  if (yyn == 52)
    return(0);
  *++yyvsp = yylval;
  yystate = yyn;
  goto yynewstate;
}
