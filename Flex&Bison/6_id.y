/*
    Program 11: YACC spec. for identifier (Bison)
    Author: Gokul Raj, 235, R7A, CSE
*/
%{
#include <stdio.h>
void yyerror(char *);
int yylex(void);
%}

%defines "tok.h"
%token NUM ALPHA NL
%start e

%%

e: s NL {printf("Accept!!\n"); YYACCEPT;}
s: ALPHA id 
id: /* ϵ */ | ALPHA id | NUM id

%%

void yyerror(char* msg){
    // Skip tokens until NL to start over
    while(yylex() != NL);
    printf("Parse Failed!! - %s\n", msg);
}

void main(){
    printf("Identifier Parser");
    while(1){
        printf("\n>> ");
        yyparse();
    }
}

/*

# OUTPUT
    $ ./id_parse
    Identifier Parser
    >> abc123
    Accept!!

    >> 12
    Parse Failed!! - syntax error

*/