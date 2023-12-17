#include "set.h"

void set_init(Set* set, char name) {
    set->name = name;
    memset(set->data, 0, SET_SIZE);
    set->size = 0;
}

char set_find(const Set* set, char element) {
    for (size_t i = 0; i < set->size; ++i)
        if (set->data[i] == element) return 1;
    return 0;
}

void set_add(Set* set, char element) {
    if (set->size < SET_SIZE && !set_find(set, element))
        set->data[set->size++] = element;
}

void set_union(Set* dest, Set* src){
    for (size_t i = 0; i < src->size; i++)
        set_add(dest, src->data[i]);
}

void set_pop(Set* set, char element) {
    size_t i = 0;
    while (i < set->size && set->data[i] != element) ++i;
    if (i < set->size) {
        memmove(&set->data[i], &set->data[i + 1], (set->size - i - 1) * sizeof(char));
        --set->size;
    }
}

void set_show(const Set* set) {
    printf("%c : { ", set->name);
    for (size_t i = 0; i < set->size; ++i) {
        if(set->data[i] == '#')
            printf("ε ");
        else
            printf("%c ", set->data[i]);
    }
    printf("}\n");
}