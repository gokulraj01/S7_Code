// Design and implement a lexical analyzer using C language
// to recognize valid tokens in the program. Also lexical analyzer should
// ignore redundant spaces, tabs and new lines.
// Ignore comment lines too.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOKEN_MAX_SIZE 256
#define BUFFER_MAX_SIZE 1024

#define isSubset(a,b,c) (c >= a && c <= b)
#define isNum(c) isSubset('0','9',c)
#define isAlpha(c) isSubset('a','z',c) && isSubSet('A','Z',c)


const char *KEYWORDS[] = {"int", "char", "double", "float", "if", "else", "elif", "switch", "while", "for", "do"};
const char *TOKEN_NAME[] = {"DTYPE", "DTYPE", "DTYPE", "DTYPE", "IF", "ELSE", "ELIF", "SWITCH", "WHILE", "FOR", "DO"};

const char *KEYWORDS[] = {"int", "char", "double", "float", "if", "else", "elif", "switch", "while", "for", "do"};
const char *TOKEN_NAME[] = {"DTYPE", "DTYPE", "DTYPE", "DTYPE", "IF", "ELSE", "ELIF", "SWITCH", "WHILE", "FOR", "DO"};

#define KEYWORDS_LEN sizeof(KEYWORDS)/sizeof(KEYWORDS[0])
#define KEYWORDS_LEN sizeof(KEYWORDS)/sizeof(KEYWORDS[0])

void err(char* msg){
    printf("[ERROR] %s\n", msg);
    exit(EXIT_FAILURE);
}

char* token, buffer;
int ti = 0, bi = 0;
FILE* f;

// Get the next chunk if chunk exists, else stop scanning
char reloadBuffer(){
    // Input one chunk to the buffer for processing
    if(buffer[bi] == 0 || bi >= BUFFER_MAX_SIZE){
        if(feof(f)) return 0;
        fgets(buffer, BUFFER_MAX_SIZE, f);
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
        token[ti] = 0;
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
    if(ki > 0){
        // Was it a keyword?
        char gotKwd = 0;
        for(int i=0; i<KEYWORDS_LEN; i++){
            if(!strncmp(KEYWORDS[i], token, TOKEN_MAX_SIZE)){
                printf("<%s,%s> ", TOKEN_NAME[i], token);
                gotKwd = 1;
                break;
            }
        }
        // No. So, it is identifier!!
        if(!gotKwd) printf("<ID,%s> ", token);
        return 1;
    }
}

char acceptOP

void main(int argc, char** argv){
    if(argc < 2) err("No input file specified!!");
    f = fopen(argv[1],"r");
    
    token = malloc(TOKEN_MAX_SIZE);
    buffer = malloc(BUFFER_MAX_SIZE);
    
    while(!reloadBuffer()){
        char c = buffer[bi];
        if(c == ' ' || c == '\t' || c == '\n'){
            bi++; continue;
        }
        acceptComment();
        acceptNum();
        acceptStr();
        
    }
}
