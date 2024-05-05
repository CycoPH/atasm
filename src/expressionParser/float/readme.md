bison -p float fullexpr.y

gcc -E -P fullexpr.tab.c > parse_float.c