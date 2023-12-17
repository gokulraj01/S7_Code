/*
    Program 11: YACC spec. for identifier (Flex)
    Author: Gokul Raj, 235, R7A, CSE
*/
%{
#include "tok.h"
%}

%%

[A-Za-z] {return ALPHA;}
[0-9] {return NUM;}
"\n" {return NL;}

%%