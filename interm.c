/*
    Program 5: Intermediate Code Generation for Simple Expressions
    Author: Gokul Raj, 235, R7A, CSE
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define STACK_SIZE 128

// Stacks for infix-postfix conversion, pseudo-evaluation
int op_top = -1, ele_top = 0;
char op_stack[STACK_SIZE], ele_stack[STACK_SIZE][8];

// Get sequential temp variables
int currTemp = 0;
int nextTemp(){ return ++currTemp; }

// Operator Precedence
int precedence(char op){
    switch(op){
        case '^': return 3;
        case '/': return 2;
        case '*': return 2;
        case '+': return 1;
        case '-': return 1;
        case '(': return 0;
        default : return -1;
    }
}

// Pop one unit (A B OP) and print 3AC for it
void pop(char last){
    int t = nextTemp();
    ele_top--;
    if(last)
        printf("e := %s %c %s\n\n", ele_stack[ele_top-1], op_stack[op_top--], ele_stack[ele_top]);
    else
        printf("t%d := %s %c %s\n", t, ele_stack[ele_top-1], op_stack[op_top--], ele_stack[ele_top]);
    sprintf(ele_stack[ele_top-1], "t%d", t);
}

void interGen(char *expr){
    int ele_i = 0;
    for(int i=0; expr[i]!=0; i++){
        int r = precedence(expr[i]);
        // If bracket end, then evaluate expr upto its beginning
        if(expr[i] == ')'){
            if(ele_i > 0) ele_stack[ele_top++][ele_i] = 0;
            ele_i = 0;
            while(op_stack[op_top] != '(') pop(0);
            op_top--;
        }

        // Not op ⇒ Part of operand
        else if(r < 0)
            ele_stack[ele_top][ele_i++] = expr[i];

        else{
            // Push current object to stack and reset counters (if not bracket)
            if(expr[i] != '('){
                if(ele_i > 0) ele_stack[ele_top++][ele_i] = 0;
                ele_i = 0;
            }
            // If stack is empty OR current precedence > stack, push to stack
            // Else, pop until lower precedence or equal (for left associativity) then push
            if(op_top >= 0 && expr[i] != '(' && r <= precedence(op_stack[op_top]))
                while(r <= precedence(op_stack[op_top])) pop(0);
            op_stack[++op_top] = expr[i];
        }
    }
    // Push last operand to stack
    if(ele_i > 0) ele_stack[ele_top++][ele_i] = 0;
    // Pop until stack is empty
    while(op_top > 0) pop(0);
    if(op_top == 0) pop(1);
}


void main(){
    char *buff = malloc(STACK_SIZE);
    printf("Enter expressions\n");
    while(1){
        // Reset stacks and counters
        op_top = -1, ele_top = 0;
        currTemp = 0;
        // Input and evaluate expression
        printf("> ");
        scanf("%s", buff);
        interGen(buff);
    }
}

/*

# OUTPUT
    Enter expressions
    > 12*3/4+2*(5+6)
    t1 := 12 * 3
    t2 := t1 / 4
    t3 := 5 + 6
    t4 := 2 * t3
    e := t2 + t4

    > 1+2
    e := 1 + 2

    > 2*3/4
    t1 := 2 * 3
    e := t1 / 4

*/