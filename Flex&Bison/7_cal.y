/*
    Program 7 - Basic Calculator using Flex & Bison (Bison)
    Author: Gokul Raj, 235, R7A, CSE
*/
%{
#include <stdio.h>
void yyerror(char *);
int yylex(void);
%}

%union{
    double val;
}

%defines "calc_tok.h"
%token <val> NUM
%token NL
%start s
%type <val> expr_brnum expr_muldiv expr

%%

s: | expr NL{printf("= %f\n", $1); YYACCEPT;}

expr:
    expr_muldiv {$$ = $1;}
    | expr_muldiv '+' expr {$$ = $1+$3;}
    | expr_muldiv '-' expr {$$ = $1-$3;}

expr_muldiv:
    expr_brnum {$$ = $1;}
    | expr_muldiv '*' expr_brnum {$$ = $1*$3;}
    | expr_muldiv '/' expr_brnum {$$ = $1/$3;}

expr_brnum:
    NUM {$$ = $1;}
    | '(' expr ')' {$$ = $2;}

%%

void yyerror(char* msg){
    printf("%s\n", msg);
}

void main(){
    printf("Bison|Flex - Basic Calculator\n");
    printf("You can use +, -, *, / operators");
    while(1){
        printf("\n>> ");
        yyparse();
    }
}

/*

# OUTPUT
    $ ./basic_calc
    Bison|Flex - Basic Calculator
    You can use +, -, *, / operators
    >> 1+2
    = 3.000000

    >> 5/2+3.3
    = 5.800000

*/