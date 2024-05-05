%{
int yylex();           
void error (char *s,int tp);
extern float nums[];
extern int vnum;
float rval;
%}
%code requires
{
    #define YYSTYPE double
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
 expr      :  expression { rval=$1; }
           ;

expression      : 'v'                       {$$=nums[vnum++]; }
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
