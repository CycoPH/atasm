Expression parser generously released to the public my Mark Schmelzenbach

Create the initial parser from the YACC definition file
> bison fullexpr.y

Run through gcc preprocessor to get code generated
> gcc -E -P fullexpr.tab.c > ph.c

Then modify to hand optimize the code.
