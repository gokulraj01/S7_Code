/*
    Program 7 - Basic Calculator using Flex&Bison
    
*/
%{
#include <stdio.h>
void yyerror(char *);
int yylex(void);
%}

%union{
    double val;
}

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