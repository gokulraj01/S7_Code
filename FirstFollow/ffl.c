#include <stdio.h>
#include <stdlib.h>
#include "set.h"

#define GRAMMAR_SIZE 8

struct Prod{
    char L;
    char R[GRAMMAR_SIZE];
    int size;
} *grammar;

Set terminals, nonterminals, nullable;
int n;

Set *firstSet, *followSet;

void first(char c, int ind){
    // If c is nullable, then add ε to first set
    if(set_find(&nullable, c)) set_add(&firstSet[ind], '#');
    // S → ɑB, add ɑ to first(B)
    for(int i=0; i<n; i++){
        for(int j=0; j<grammar[i].size; j++){
            if(grammar[i].R[j] == c){
                // If there is charecter before it and it is NT, add to first
                if(j > 0 && grammar[i].R[j] < 'A' && grammar[i].R[j] > 'Z')
                    set_add(&firstSet[ind], grammar[i].R[j-1]);
                // Rule3: Else, first of LHS is first of current NT
                else
                    // Find index of LHS in firstSet, then copy its elements
                    for(int k=0; k<nonterminals.size; k++)
                        if(firstSet[k].name == grammar[i].L)
                            for(int l=0; l<firstSet[k].size; l++)
                                set_add(&firstSet[ind], firstSet[k].data[l]);
            }
        }
    }
}

void follow(char c){

}

int main(int argc, char **argv){
    printf("First&Follow\nInput without spaces |  \'#\' is ε | A-Z are terminals, rest non-terminals\n");
    set_init(&nullable, 0);
    grammar = malloc(sizeof(struct Prod)*n);
    printf("No: of Productions: ");
    scanf("%d", &n);
    
    // Input the grammar productions
    for(int i=0; i<n; i++){
        scanf(" %c -> %s", &grammar[i].L, grammar[i].R);
        grammar[i].size = 0;
        while(grammar[i].R[grammar[i].size] != 0) grammar[i].size++;
        // LHS is a guarenteed NT
        set_add(&nonterminals, grammar[i].L);
        // If RHS is epsilon, then set LHS as nullable
        if(!strncmp(grammar[i].R, "#", grammar[i].size)) set_add(&nullable, grammar[i].L);
        // Else, find and push all NTs to set 
        else{
            for(int j=0; j<grammar[i].size; j++)
                if(grammar[i].R[j] < 'A' || grammar[i].R[j] > 'Z')
                    set_add(&nonterminals, grammar[i].R[j]);
        }
    }

    // Init firstSets and followSets
    firstSet = malloc(sizeof(Set)*nonterminals.size);
    memset(firstSet, 0, sizeof(Set)*nonterminals.size);
    followSet = malloc(sizeof(Set)*nonterminals.size);
    memset(followSet, 0, sizeof(Set)*nonterminals.size);
    
    // Compute first and follow sets
    for(int i = 0; i < nonterminals.size; i++) first(nonterminals.data[i], i);
    for(int i = 0; i < nonterminals.size; i++) follow(nonterminals.data[i]);
    
    return EXIT_SUCCESS;
}