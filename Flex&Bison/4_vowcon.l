/* 
    Program 9: Count vowels and consonants using Flex
    Author: Gokul Raj, 235, R7A, CSE
*/
%{
// NOTE: Compile with '-i' flag for case insensitivity
#include <stdio.h>
// Initalize vowel and consonant counters
int vow = 0, cons = 0;
%}

%%
    /* If vowel, increment vowel counter */
"a"|"e"|"i"|"o"|"u" { vow++; }
    /* Else, if valid A-Z char, increment consonant counter */
[A-Za-z] { cons++; }
    /* Ignore other charecters */
"\n"|. {}
%%

int main(int argc, char **argv){
    if(argc < 2){
        printf("[ERROR] No input file provided!!\n");
        return 1;
    }
    printf("Reading file %s...\n", argv[1]);
    yyin = fopen(argv[1], "r");
    yylex();

    // Display summary
    printf("Vowels: %d, Consonants: %d\n", vow, cons);
    return 0;
}

/* 

# INPUT - test4.txt
    aEiOu
    cat
    bow

# OUTPUT
    $ ./vowcon test4.txt
    Reading file test4.txt...
    Vowels: 5, Consonants: 6

*/