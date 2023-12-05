/*
    Program 2 - Recursive Decent Parser
    Create a program implementing recursive descent parser for
    a simple calculator using the following grammar
    
    E  -> TE'
    E' -> +TE' | -TE' | ε
    T  -> FT'
    T' -> *FT' | /FT' | ε
    F  -> (E) | N
    N -> {0..9}
    
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void err(char *msg){
    printf("[ERROR] %s\n", msg);
    exit(EXIT_FAILURE);
}

int findDelim(char *s, char delim, int l){
    int i = 0;
    while(i < l){
        if(s[i] == delim) return i;
        i++;
    }
    return -1;
}


// Function declarations
char E(char *s, int l);
char F(char *s, int l);
char G(char *s, int l);
char N(char *s, int l);

char shb[64];

char* shown(char *s, int l){
    strncpy(shb, s, l);
    shb[l] = 0;
    return shb;
}

char N(char *s, int l){
    printf("N? -> %s\n", shown(s,l));
    for(int i=0; i<l; i++)
        if((s[i] <= '0' || s[i] >= '9') && s[i] != ' ' && s[i] != '\n') return 0;
    printf("Yes!!\n");
    return 1;
}

char G(char *s, int l){
    printf("G? -> %s\n", shown(s,l));
    int i = findDelim(s,'(',l);
    int j = findDelim(s,')',l);
    printf("( at %d ) at %d\n", i, j);
    if(i == -1 || j == -1) return N(s, l);
    else return E(&s[i+1], j-i-1);
}

char F(char *s, int l){
    printf("F? -> %s\n", shown(s,l));
    int i = findDelim(s,'*',l);
    int j = findDelim(s,'/',l);
    printf("* at %d / at %d\n", i, j);
    char res = 0;
    res = res || G(s,l);
    if(i > -1 && !res) res = res || F(s, i) && G(&s[i+1], l-i-1);
    if(j > -1 && !res) res = res || F(s, j) && G(&s[j+1], l-j-1);
    
    return res;
}

char E(char *s, int l){
    printf("E? -> %s\n", shown(s,l));
    int i = findDelim(s,'+',l);
    int j = findDelim(s,'-',l);
    printf("+ at %d - at %d\n", i, j);
    char res = 0;
    res = res || F(s,l);
    if(i > -1 && !res) res = res || E(s, i) && F(&s[i+1], l-i-1);
    if(j > -1 && !res) res = res || E(s, j) && F(&s[j+1], l-j-1);
    
    return res;
}

void main(int argc, char **argv){
    char buff[256];
    while(1){
        printf(">> ");
        fgets(buff, 256, stdin);
        int l = strlen(buff)-1;
        buff[l] = 0;
        if(!E(buff, l)) printf("Parse failed!!\n");
    }
}
