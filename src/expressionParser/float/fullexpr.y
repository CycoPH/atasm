%{
int yylex();           
void error (char *s,int tp);
extern float fnums[];
extern int fvnum;
float frval;
%}
%code requires
{
    #define YYSTYPE double
	#define __builtin_memcpy memcpy
}

/*  Operator precedence
[  ]  psuedo parentheses

.-        unary minus

.NOT(N)  unary logical.  Returns true (1) if expression
         is zero.  Returns false (0) it expression is
         non-zero.

/        division
*        multiplication

+        addition
-        subtraction

=        equality, logical
>        greater than, logical
<        less than, logical
<>(#)    inequality, logical
>=(G)    greater or equal, logical
<=(L)    less or equal, logical

*/

%left   '=' '#' '<' '>' 'G' 'L'
%left   '+' '-'
%left   '*' '/'
%right  'N'
%right  '!' 'R' 'D'

%start expr


%%
 expr      :  expression { frval=$1; }
           ;

expression      : 'v'                       {$$=fnums[fvnum++]; }
                | 'N' expression            {$$=!$2; }
                | '-' expression %prec '!'  {$$=-($2); } 
                | expression '+' expression {$$=$1+$3; }
                | expression '-' expression {$$=$1-$3; }
                | expression '*' expression {$$=$1*$3; }
                | expression '/' expression {$$=$1/$3; }
                | expression '<' expression {$$=($1<$3); }
                | expression '>' expression {$$=($1>$3); }
                | expression 'L' expression {$$=($1<=$3); }
                | expression 'G' expression {$$=($1>=$3); }
                | expression '=' expression {$$=($1==$3); }
                | expression '#' expression {$$=($1!=$3); } 
                | '[' expression ']' {$$=$2;}               
                ;

%%
