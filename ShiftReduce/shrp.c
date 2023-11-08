// Program 3: Shift-Reduce Parser
#include <stdio.h>
#include <stdlib.h>

#define GRAMMAR_LEFT_SIZE 2
#define GRAMMAR_RIGHT_SIZE 8
#define STACK_SIZE 128

struct Prod{
    char L[GRAMMAR_LEFT_SIZE];
    char R[GRAMMAR_RIGHT_SIZE];
};

struct Prod *grammar;
char stack[STACK_SIZE];
int n, top = -1;

char reducible(){
    for(int i=0; i<n; i++){
        int j = top;
        
    }
}

void main(){
    grammar = malloc(sizeof(struct Prod)*n);
    printf("No: of Productions: ");
    scanf("%d", &n);
    // Input the grammar productions
    for(int i=0; i<n; i++)
        scanf("%s -> %s", grammar[i].L, grammar[i].R);
    

}