/*
    Program 13: Optimization | Constant Propogation
    Author: Gokul Raj, 235, R7A, CSE
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define VAR_SIZE 8

typedef struct{
    char name;
    int value;
} Symbol;

// One for each lowercase alphabet
Symbol symtab[26];

int evaluate(char *a, char op, char *b){
    int val_a, val_b;
    // Evaluate A
    if(isdigit(a[0])) val_a = atoi(a);
    else val_a = symtab[tolower(a[0])-'a'].value;
    // Evaluate B
    if(isdigit(b[0])) val_b = atoi(b);
    else val_b = symtab[tolower(b[0])-'a'].value;
    // Evaluate and return final result
    switch(op){
        case '+': return val_a + val_b;
        case '-': return val_a - val_b;
        case '*': return val_a * val_b;
        case '/': return val_a / val_b;
        default: return 0;
    }
}

void main(){
    char a, b[VAR_SIZE], c[VAR_SIZE], op, n;
    char buf[128];
    printf("Constant Propogation\n");
    printf("Enter expressions\n>> ");
    while(fgets(buf, 128, stdin)){
        int match = sscanf(buf, " %c = %s %c %s", &a, b, &op, c);
        a = tolower(a);
        n = a-'a';
        // When format is a = b
        if(match == 2){
            symtab[n].name = a;
            symtab[n].value = atoi(b);
        }
        // Else when format is a = b op c
        else if(match == 4){
            symtab[n].name = a;
            symtab[n].value = evaluate(b, op, c);
        }
        else{
            printf("Syntax Error!!\n");
            exit(EXIT_FAILURE);
        }
        printf(" ↳ %c = %d\n", symtab[n].name, symtab[n].value);
        printf("\n>> ");
    }
}