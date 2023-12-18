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
#include <stdlib.h>
#include <string.h>

char buff[256];

char E(int *i);

char N(int *i){
    char match = 0;
    while(buff[*i] >= '0' && buff[*i] <= '9'){
        match = 1;
        ++(*i);
    }
    return match;
}

char F(int *i){
    if(buff[*i] == '('){
        i++;
        if(!E(i)) return 0;
        if(buff[*i] == ')'){
            ++(*i);
            return 1;
        }
    }
    return N(i);
}

char T_(int *i){
    if(buff[*i] == '*' || buff[*i] == '/'){
        ++(*i);
        return F(i) && T_(i);
    }
    return 1;
}

char T(int *i){
    return F(i) && T_(i);
}

char E_(int *i){
    if(buff[*i] == '+' || buff[*i] == '-'){
        ++(*i);
        return T(i) && E_(i);
    }
    return 1;
}

char E(int *i){
    return T(i) && E_(i);
}

void main(int argc, char **argv){
    while(1){
        printf(">> ");
        fgets(buff, 256, stdin);
        int l = strlen(buff)-1;
        buff[l] = 0;
        int ind = 0;
        if(!E(&ind)) printf("Parse failed!!\n");
    }
}

/*

# OUTPUT
    $ ./rec_descent
    >> 1 + 2
    >> 1 * 2/3
    >> 5/6 * 7/8
    >> )-1
    Parse failed!!
    >> *3+3
    Parse failed!!

*/