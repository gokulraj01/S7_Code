/* 
    Program 3: Shift-Reduce Parser
    Author: Gokul Raj, 235, R7A, CSE
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define GRAMMAR_SIZE 8
#define STACK_SIZE 128

struct Prod{
    char L;
    char R[GRAMMAR_SIZE];
    int size;
};

struct Prod *grammar;
char stack[STACK_SIZE];
int n, top = -1;

char reducible(char *s, char ind){
    if(top == -1) return 0;
    for(int i=0; i<n; i++){
        int j = top;
        int k = grammar[i].size-1;
        if(k < 0) continue;
        while(k >= 0 && j >= 0){
            if(grammar[i].R[k] != stack[j]) break;
            j--; k--;
        }
        // If reducible pop RHS from stack
        // then push LHS of production
        if(k < 0){
            for(k=0; k<grammar[i].size; k++) top--;
            stack[++top] = grammar[i].L;
            printf("%s\t%s\tREDUCE %c->%s\n", stack, &s[ind], grammar[i].L, grammar[i].R);
            return 1;
        }
    }
    return 0;
}

void main(){
    char startSym;
    grammar = malloc(sizeof(struct Prod)*n);
    printf("No: of Productions: ");
    scanf("%d", &n);
    // Input the grammar productions
    for(int i=0; i<n; i++){
        scanf(" %c -> %s", &grammar[i].L, grammar[i].R);
        grammar[i].size = 0;
        while(grammar[i].R[grammar[i].size] != 0) grammar[i].size++;
    }

    // Get start symbol
    printf("Start Symbol: ");
    while(isspace(startSym = getchar()));
    getchar();
    while(1){
        // Input userstring to check grammar, reset stack
        char *s = malloc(STACK_SIZE);
        printf(">> "); scanf("%s", s);
        top = -1;

        // Process until string end or parse error
        printf("Stack\tInput\tOperation\n");
        int i = 0;
        while(s[i] != 0 && s[i] != '\n'){
            // Reduce if possible
            while(reducible(s, i));
            // Else shift
            stack[++top] = s[i];
            stack[top+1] = 0;
            printf("%s\t%s\tSHIFT %c\n", stack, &s[i+1], s[i]);
            i++;
        }
        // Check if any reductions pending
        while(reducible(s, i));
        // If parse done, stack top has start symbol only
        if(top == 0 && stack[top] == startSym)
            printf("Parsed!!\n");
        else
            printf("[ERROR] Syntax error!!\n");
    }
}