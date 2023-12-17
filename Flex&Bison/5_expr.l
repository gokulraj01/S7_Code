/*
    Program 10: YACC spec. for arithmetic expressions (Flex)
    Author: Gokul Raj, 235, R7A, CSE
*/
%{
#include "tok.h"
%}

%%

[0-9]+ {return NUM;}
"\n" {return NL;}
. {return *yytext;}

%%