// Author: Gokul Raj, 235, R7A, CSE

/*  Program 1 - Lexer using C

    Design and implement a lexical analyzer using C language
    to recognize valid tokens in the program. Also lexical analyzer should
    ignore redundant spaces, tabs and new lines.
    Ignore comment lines too.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOKEN_MAX_SIZE 256
#define OP_MAX_SIZE 3
#define BUFFER_MAX_SIZE 1024

#define isSubset(a,b,c) (c >= a && c <= b)
#define isNum(c) (c >= '0' && c <= '9')
#define isAlpha(c) (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')

const char *KEYWORDS[] = {"int", "char", "double", "float", "if", "else", "elif", "switch", "while", "for", "do"};
const char *KW_NAME[] = {"DTYPE", "DTYPE", "DTYPE", "DTYPE", "IF", "ELSE", "ELIF", "SWITCH", "WHILE", "FOR", "DO"};

const char *OPERATORS[] = {">", "<", ">=", "<=", "==", "!=", "||", "&&", "!", "=", "&", "|", "^", "~", "+", "-", "*", "/", "%", "(", ")"};
const char *OP_NAME[] = {"RELOP", "RELOP", "RELOP", "RELOP", "RELOP", "RELOP", "LOP", "LOP", "LOP", "EQ", "BOP", "BOP", "BOP", "BOP", "AOP", "AOP", "AOP", "AOP", "AOP", "BR_OPEN", "BR_CLOSE"};

#define KW_LEN sizeof(KEYWORDS)/sizeof(KEYWORDS[0])
#define OP_LEN sizeof(OPERATORS)/sizeof(OPERATORS[0])

void err(char* msg){
    printf("[ERROR] %s\n", msg);
    exit(EXIT_FAILURE);
}

char *token, *buffer;
int ti = 0, bi = 0;
FILE* f;

// Get the next chunk if chunk exists, else stop scanning
char reloadBuffer(){
    // Input one chunk to the buffer for processing
    if(buffer[bi] == 0 || bi >= BUFFER_MAX_SIZE){
        if(fgets(buffer, BUFFER_MAX_SIZE, f) == NULL) return 0;
        putchar('\n');
        bi = 0;
    }
    return 1;
}

// Check if the next sequence is a set of digits
char acceptNum(){
    while(isNum(buffer[bi])){
        token[ti++] = buffer[bi++];
        reloadBuffer();
    }
    if(ti > 0){
        token[ti++] = 0;
        printf("<NUM,%s> ", token);
        ti = 0;
        return 1;
    }
    return 0;
}

// Accept and ignore comments
char acceptComment(){
    if(buffer[bi] == '#'){
        // Skip everything upto new line
        while(buffer[bi] != '\n'){
            bi++;
            reloadBuffer();
        }
        bi++;
        ti = 0;
        return 1;
    }
    return 0;
}

// Accept strings and check if they are identifiers or keywords
char acceptStr(){
    while(isAlpha(buffer[bi]) || buffer[bi] == '_'){
        token[ti++] = buffer[bi++];
        reloadBuffer();
    }
    // Did we get anything?
    if(ti > 0){
        token[ti++] = 0;
        // Was it a keyword?
        char gotKwd = 0;
        for(int i=0; i<KW_LEN; i++){
            if(!strncmp(KEYWORDS[i], token, TOKEN_MAX_SIZE)){
                printf("<KWD:%s,%s> ", KW_NAME[i], token);
                gotKwd = 1;
                break;
            }
        }
        // No. So, it is identifier!!
        if(!gotKwd) printf("<ID,%s> ", token);
        ti = 0;
        return 1;
    }
}

char acceptOP(){
    while(!isAlpha(buffer[bi])){
        if(buffer[bi] != ' ' && buffer[bi] != '\t' && buffer[bi] != '\n' && buffer[bi] != ';'){
            token[ti++] = buffer[bi++];
            reloadBuffer();                
        }
        else{
            bi++; break;
        }
    }
    // Did we get anything?
    if(ti > 0){
        token[ti] = 0;
        ti = 0;
        // Was it a keyword?
        for(int i=0; i<OP_LEN; i++){
            if(!strncmp(OPERATORS[i], token, OP_MAX_SIZE)){
                printf("<OP:%s,%s> ", OPERATORS[i], token);
                return 1;
            }
        }
        return 0;
    }
}

void main(int argc, char** argv){
    if(argc < 2) err("No input file specified!!");
    f = fopen(argv[1],"r");
    
    token = malloc(TOKEN_MAX_SIZE);
    buffer = malloc(BUFFER_MAX_SIZE);
    
    while(reloadBuffer()){
        char c = buffer[bi];
        if(c == ' ' || c == '\t' || c == '\n'){
            bi++; continue;
        }
        acceptComment();
        acceptNum();
        acceptStr();
        acceptOP();
    }
}

/*

# INPUT - testfile.txt
int a = 10;
int b = 12;

# This is a comment line which is ignored
if(a < 10 && b != 10){
    b = a;
    a = 10;
}

# OUTPUT
$ ./lexer testfile.txt

<KWD:DTYPE,int> <ID,a> <OP:=,=> <NUM,10> 
<KWD:DTYPE,int> <ID,b> <OP:=,=> <NUM,12> 


<KWD:IF,if> <OP:(,(> <ID,a> <OP:<,<> <NUM,10> <OP:&&,&&> <ID,b> <OP:!=,!=> <NUM,10> 
<ID,b> <OP:=,=> <ID,a> 
<ID,a> <OP:=,=> <NUM,10>

*/
