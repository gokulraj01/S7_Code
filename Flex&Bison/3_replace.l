/* 
    Program 8: Replace 'abc' with 'ABC' from input using Flex
    Author: Gokul Raj, 235, R7A, CSE
*/
%{
#include <stdio.h>
%}

%%

"abc" {printf("ABC");}
"\n" {printf("\n>> ");}
. {putchar(yytext[0]);}

%%

int main(int argc, char **argv){
    printf("Enter prompts.\nFlex will replace all instance of 'abc' with 'ABC'\n>> ");
    yylex();
    return 0;
}

/* 

# OUTPUT
    $ ./replace
    Enter prompts.
    Flex will replace all instance of 'abc' with 'ABC'
    >> helloabcworld
    helloABCworld
    >> asjkdhabchjakdabcjahkdjabckhjkajhabahkjkjabc
    asjkdhABChjakdABCjahkdjABCkhjkajhabahkjkjABC

*/