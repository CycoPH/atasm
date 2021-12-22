%{
int yylex();           
void error (char *s,int tp);
extern int nums[];
extern int vnum;
int rval;
%}

/*  Operator precedence
[  ]  psuedo parentheses

.DEF(D)  unary logical label definition.  Returns true
         if label is defined.
.REF(R)  unary logical label reference.  Returns true if
         label has been referenced.
>        unary.  Returns the high byte of the expression.
<        unary.  Returns the low byte of the expression.
-        unary minus

.NOT(N)  unary logical.  Returns true (1) if expression
         is zero.  Returns false (0) it expression is
         non-zero.

/        division
*        multiplication
%% .MOD(M)  modulus

+        addition
-        subtraction

<<(Q)	shift left
>>(W)	shift rught

&        binary AND
|        binary OR
^        binary EOR

=        equality, logical
>        greater than, logical
<        less than, logical
<>(#)    inequality, logical
>=(G)    greater or equal, logical
<=(L)    less or equal, logical

.AND(A)  logical AND

.OR(R)   logical OR

*/

%left   'O'
%left   'A'
%left   '=' '#' '<' '>' 'G' 'L'
%left   '&' '|' '^'
%left   'Q' 'W'
%left   '+' '-'
%left   '*' '/' 'M'
%right  'N'
%right  '!' 'R' 'D'

%start expr


%%
 expr      :  expression { rval=$1; }
           ;

expression      : 'v'                       {$$=nums[vnum++]; }
                | 'N' expression            {$$=!$2; }
                | '>' expression %prec '!'  {$$=(($2)>>8)&0xff; }
                | '<' expression %prec '!'  {$$=($2)&0xff; }
                | '-' expression %prec '!'  {$$=-($2); } 
                | expression '|' expression {$$=$1|$3; }
                | expression '&' expression {$$=$1&$3; }
                | expression '^' expression {$$=$1^$3; }
				| expression 'Q' expression {$$=$1<<$3; }
				| expression 'W' expression {$$=$1>>$3; }
                | expression '+' expression {$$=$1+$3; }
                | expression '-' expression {$$=$1-$3; }
				| expression 'M' expression {$$=$1%$3; }
                | expression '*' expression {$$=$1*$3; }
                | expression '/' expression {$$=$1/$3; }
                | expression '<' expression {$$=($1<$3); }
                | expression '>' expression {$$=($1>$3); }
                | expression 'L' expression {$$=($1<=$3); }
                | expression 'G' expression {$$=($1>=$3); }
                | expression '=' expression {$$=($1==$3); }
                | expression '#' expression {$$=($1!=$3); } 
                | expression 'A' expression {$$=($1&&$3); }
                | expression 'O' expression {$$=($1||$3); }
                | '[' expression ']' {$$=$2;}               
                ;

%%
