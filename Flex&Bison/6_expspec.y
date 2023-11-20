%{
#include <stdio.h>
void yyerror(char *);
int yylex(void);
%}

%token NUM ALPHA

%%

s: ALPHA id
id: /* ϵ */ | ALPHA id | NUM id

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