/*
    Program 2 - Recursive Decent Parser
    Create a program implementing recursive descent parser for
    a simple calculator using the following grammar
    
    E -> F | E+F | E-F
    F -> G | F*G | F/G
    G -> (E) | N
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
    printf("checking '%s' [len:%d] for '%c'\n", s, l, delim);
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


char N(char *s, int l){
    for(int i=0; i<l; i++)
        if(s[i] <= '0' || s[i] >= '9') return 0;
    return 1;
}

char G(char *s, int l){
    int i = findDelim(s,'(',l);
    int j = findDelim(s,')',l);
    if(i == -1 || j == -1) return N(s, l);
    else return E(&s[i+1], j-i-1);
}

char F(char *s, int l){
    int i = findDelim(s,'*',l);
    int j = findDelim(s,'/',l);
    
    char res = 0;
    res = res || G(s,l);
    if(i > -1) res = res || F(s, i) && G(&s[i], l-i);
    if(j > -1) res = res || F(s, j) && G(&s[j], l-j);
    
    return res;
}

char E(char *s, int l){
    int i = findDelim(s,'+',l);
    int j = findDelim(s,'-',l);
    
    char res = 0;
    res = res || F(s,l);
    if(i > -1) res = res || E(s, i) && F(&s[i], l-i);
    if(j > -1) res = res || E(s, j) && F(&s[j], l-j);
    
    return res;
}

void main(int argc, char **argv){
    char buff[256];
    while(1){
        printf(">> ");
        fgets(buff, 256, stdin);
        int l = strlen(buff);
        if(!E(buff, l)) printf("Parse failed!!\n");
    }
}
