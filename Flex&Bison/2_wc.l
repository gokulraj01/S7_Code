/* 
    Program 7: Word Count using Flex
    Author: Gokul Raj, 235, R7A, CSE
*/
%{
#include <stdio.h>
// Initialize counters for wc program
int lines = 0, words = 0, chars = 0;
char wf = 0;
%}

%%
"\n" {
    lines++;
    // Skip blank lines
    if(wf) words++;
    wf = 0;
    chars++;
}
" " {words++; chars++;}
. {chars++; wf = 1;}
%%

int main(int argc, char **argv){
    if(argc < 2){
        printf("[ERROR] No input file provided!!\n");
        return 1;
    }
    printf("Reading file %s...\n", argv[1]);
    yyin = fopen(argv[1], "r");
    yylex();

    // Fix counts wrt. other counts
    if(chars > 0){
        lines++; words++;
    }
    // Display summary of wc program
    printf("Lines: %d, Words: %d, Chars: %d\n", lines, words, chars);

    return 0;
}

/*

# INPUT - test2.txt
    hello world


    this is a sample file to test lex word count

# OUTPUT
    $ ./wc test2.txt
    Reading file test2.txt...
    Lines: 4, Words: 12, Chars: 58

*/