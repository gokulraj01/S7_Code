#include <stdio.h>
#include <stdlib.h>
#include "set.h"

#define GRAMMAR_SIZE 8
#define LOG(x) printf("[DBG:%d] %s\n", __LINE__, x)
#define VARDUMP(x) printf("[%s] %s\n", #x, x)
#define INTDUMP(x) printf("[%s] %d\n", #x, x)

struct Prod{
    char L;
    char R[GRAMMAR_SIZE];
    int size;
} *grammar;

Set terminals, nonterminals, nullable;
char language[SET_SIZE*2];
int grammar_n, terms_n;

Set *firstSet, *followSet;

/*
// S → ɑB, add ɑ to first(B)
for(int i=0; i<grammar_n; i++){
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
*/

Set* first(char c){
    int ind;
    // If already found, then return its index
    for(int i=0; i<terms_n; i++){
        if(language[i] == c){
            ind = i;
            if(firstSet[i].name == c) return &firstSet[ind];
            break;
        }
    }
    // Mark current set as evaluated
    firstSet[ind].name = c;

    // If terminal A, then first(A) = A 
    if(set_find(&terminals, c)){
        set_add(&firstSet[ind], c);
        return &firstSet[ind];
    }
    
    // If A -> αB, then add first(α) to first(A)
    for(int i=0; i<grammar_n; i++){
        int j = 0;
        if(grammar[i].L == c && grammar[i].R[0] != '#'){
            // If α is nullable, then proceed union until end, or 1st non nullable term
            while(j<grammar[i].size && set_find(&nullable, grammar[i].R[j])){
                set_union(&firstSet[ind], first(grammar[i].R[j]));
                j++;
            }
            // If all terms nullable, then add ε to first(A), else pop ∈
            if(j < grammar[i].size){
                set_union(&firstSet[ind], first(grammar[i].R[j]));
                set_pop(&firstSet[ind], '#');
            }
        }
    }

    // If c is nullable, then add ε to first set
    // Do this last because we may pop ε in a last step if some other set had it
    if(set_find(&nullable, c)) set_add(&firstSet[ind], '#');

    return &firstSet[ind];
}

void follow(char c){
    
}

int main(int argc, char **argv){
    printf("First&Follow\nInput without spaces |  \'#\' is ε | A-Z are non-terminals, rest terminals\n");
    set_init(&nullable, 0);
    printf("No: of Productions: ");
    scanf("%d", &grammar_n);
    
    // Input the grammar productions
    grammar = malloc(sizeof(struct Prod)*grammar_n);
    for(int i=0; i<grammar_n; i++){
        scanf(" %c -> %s", &grammar[i].L, grammar[i].R);
        grammar[i].size = 0;
        while(grammar[i].R[grammar[i].size] != 0) grammar[i].size++;
        // LHS is a guarenteed NT
        set_add(&nonterminals, grammar[i].L);
        // If RHS is epsilon, then set LHS as nullable
        if(!strncmp(grammar[i].R, "#", grammar[i].size)) set_add(&nullable, grammar[i].L);
        // Else, find and push all NTs to set 
        else{
            for(int j=0; j<grammar[i].size; j++){
                if(grammar[i].R[j] >= 'A' && grammar[i].R[j] <= 'Z')
                    set_add(&nonterminals, grammar[i].R[j]);
                else
                    set_add(&terminals, grammar[i].R[j]);
            }
        }
    }

    // Init firstSets and followSets
    terms_n = nonterminals.size + terminals.size;
    language[0] = 0;
    
    strncat(language, terminals.data, terminals.size);
    strncat(language, nonterminals.data, nonterminals.size);
    firstSet = malloc(sizeof(Set)*terms_n+100);
    memset(firstSet, 0, sizeof(Set)*terms_n);
    followSet = malloc(sizeof(Set)*nonterminals.size);
    memset(followSet, 0, sizeof(Set)*nonterminals.size);
    
    // Compute first and follow sets
    printf("--\nFirst Sets\n");
    for(int i = 0; i < nonterminals.size; i++) set_show(first(nonterminals.data[i]));
    printf("--\nFollow Sets\n");
    // for(int i = 0; i < nonterminals.size; i++) follow(nonterminals.data[i]);
    return EXIT_SUCCESS;
}