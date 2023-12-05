%{
#include <stdio.h>
#include "calc_tok.h"
%}

%%
    /* Number clause */
([0-9]*\.[0-9]+|[0-9]+) {
    yylval.val = atof(yytext);
    return NUM;
}

"\n" {return NL;}

[ \t]* {}

. {return *yytext;}

%%