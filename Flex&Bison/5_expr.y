/*
    Program 10: YACC spec. for arithmetic expressions (Bison)
    Author: Gokul Raj, 235, R7A, CSE
*/
%{
#include <stdio.h>
void yyerror(char *);
int yylex(void);
%}

%defines "tok.h"
%token NUM NL
%start s

%%

s: | expr NL {printf("Accept!!\n"); YYACCEPT;}

expr:
    expr_muldiv
    | expr_muldiv '+' expr
    | expr_muldiv '-' expr

expr_muldiv:
    expr_brnum
    | expr_muldiv '*' expr_brnum
    | expr_muldiv '/' expr_brnum

expr_brnum:
    NUM
    | '(' expr ')'

%%

void yyerror(char* msg){
    // Skip tokens until NL to start over
    while(yylex() != NL);
    printf("Parse Failed!! - %s\n", msg);
}

void main(){
    printf("Expression Parser");
    while(1){
        printf("\n>> ");
        yyparse();
    }
}

/*

# OUTPUT
    $ ./exp_parse
    Expression Parser
    >> (1+2)/3*4-5
    Accept!!

    >> 3--2
    Parse Failed!! - syntax error

*/