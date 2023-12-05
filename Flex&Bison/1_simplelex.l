/* 
    Program 6: Simple lexical analyzer using Flex
    Author: Gokul Raj, 235, R7A, CSE
*/
%{
// NOTE: Compile with '-i' flag for case insensitivity
#include <stdio.h>
%}

%%
    /* Ignore comments */
#.* {}

    /* Number clause */
([0-9]*\.[0-9]+|[0-9]+) {printf("<NUM,%s>", yytext);}

    /* Keyword tokens */
"int" {printf("<KWD:DTYPE, %s> ", yytext);}
"char" {printf("<KWD:DTYPE, %s> ", yytext);}
"double" {printf("<KWD:DTYPE, %s> ", yytext);}
"float" {printf("<KWD:DTYPE, %s> ", yytext);}
"if" {printf("<KWD:if>");}
"else" {printf("<KWD:else>");}
"elif" {printf("<KWD:elif>");}
"while" {printf("<KWD:while>");}
"do" {printf("<KWD:do>");}
"for" {printf("<KWD:for>");}
"switch" {printf("<KWD:switch>");}
"case" {printf("<KWD:case>");}

    /* Condition tokens */
"<" {printf("<KWD:RELOP,%s> ", yytext);}
">" {printf("<KWD:RELOP,%s> ", yytext);}
">=" {printf("<KWD:RELOP,%s> ", yytext);}
"<=" {printf("<KWD:RELOP,%s> ", yytext);}
"==" {printf("<KWD:RELOP,%s> ", yytext);}
"!=" {printf("<KWD:RELOP,%s> ", yytext);}
"||" {printf("<KWD:LOP,%s> ", yytext);}
"&&" {printf("<KWD:LOP,%s> ", yytext);}
"!" {printf("<KWD:LOP,%s> ", yytext);}
"=" {printf("<KWD:EQ,%s> ", yytext);}
"&" {printf("<KWD:BOP,%s> ", yytext);}
"|" {printf("<KWD:BOP,%s> ", yytext);}
"^" {printf("<KWD:BOP,%s> ", yytext);}
"~" {printf("<KWD:BOP,%s> ", yytext);}
"+" {printf("<KWD:AOP,%s> ", yytext);}
"-" {printf("<KWD:AOP,%s> ", yytext);}
"*" {printf("<KWD:AOP,%s> ", yytext);}
"/" {printf("<KWD:AOP,%s> ", yytext);}
"%" {printf("<KWD:AOP,%s> ", yytext);}
"(" {printf("<KWD:BR_OPEN,%s> ", yytext);}
")" {printf("<KWD:BR_CLOSE,%s> ", yytext);}

    /* Identifier clause */
[a-zA-Z][a-zA-Z0-9]* { printf("<ID,%s> ", yytext);}

    /* New lines and whitespace skip */
[\n]* {putchar('\n');}
[ \t] {}

    /* Catch all clause */
. {printf(" \'%s\' ", yytext);}

%%

int main(int argc, char **argv){
    if(argc < 2){
        printf("[ERROR] No input file provided!!\n");
        return 1;
    }
    printf("Reading file %s...\n", argv[1]);
    yyin = fopen(argv[1],"r");
    yylex();
    return 0;
}

/* 

# INPUT - test1.txt
    int a = 10;
    int b = 12;

    # This is a comment line which is ignored
    if(a < 10 && b != 10){
        b = a;
        a = 10;
    }

# OUTPUT
    $ ./simplelex test1.txt
    Reading file test1.txt...
    <KWD:DTYPE, int> <ID,a> <KWD:EQ,=> <NUM,10> ';' 
    <KWD:DTYPE, int> <ID,b> <KWD:EQ,=> <NUM,12> ';' 

    <KWD:if><KWD:BR_OPEN,(> <ID,a> <KWD:RELOP,<> <NUM,10><KWD:LOP,&&> <ID,b> <KWD:RELOP,!=> <NUM,10><KWD:BR_CLOSE,)>  '{' 
    <ID,b> <KWD:EQ,=> <ID,a>  ';' 
    <ID,a> <KWD:EQ,=> <NUM,10> ';' 
    '}'

*/