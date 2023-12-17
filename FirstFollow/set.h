#include <stdio.h>
#include <string.h>

#define SET_SIZE 16

typedef struct {
    char name;
    char data[SET_SIZE];
    size_t size;
} Set;

void set_init(Set* set, char name);

char set_find(const Set* set, char element);

void set_add(Set* set, char element);
void set_union(Set* dest, Set* src);

void set_pop(Set* set, char element);

void set_show(const Set* set);