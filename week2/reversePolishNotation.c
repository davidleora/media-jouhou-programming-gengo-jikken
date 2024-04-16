#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100
#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define FAILURE 0

typedef char data_type;
typedef struct node_tag {
    data_type data;
    struct node_tag *next;
} node_type;

void initialize(node_type **pp){
    *pp = NULL;
}

int is_empty(node_type *p){
    return (p == NULL) ? TRUE : FALSE;
}

data_type top(node_type *p){
    if (is_empty(p)){
        printf("スタックは空です\n");
        return '\0';
    }
    return p->data;
}

node_type *new_node(data_type x, node_type *next) {
    node_type *temp = (node_type *)malloc(sizeof(node_type));
    if (temp != NULL) {
        temp->data = x;
        temp->next = next;
    }
    return temp;
}

int push(data_type x, node_type **pp){
    node_type *temp = new_node(x, *pp);
    if (temp == NULL) return FAILURE;
    *pp = temp;
    return SUCCESS;
}

int pop(node_type **pp)
{
    node_type *temp;

    if (!is_empty(*pp)){
        temp = (*pp)->next;
        free(*pp);
        *pp = temp;
        return SUCCESS;
    }
    return FAILURE;
}

int checkPriority(char a){
    int priority;
    switch (a) {
        case '=':
            return 0;
        case ')' :
            return 1;
        case '+' :
            return 2;
        case '-' :
            return 2;
        case '*' :
            return 3;
        case '/' : 
            return 3;
        case '(' : 
            return 4;
        default:
            return 5;
        }
}

int main(){
    node_type *stack;
    initialize(&stack);
    char input[SIZE];
    int track = 0;
    scanf("%s", input);

    while (track < strlen(input) && input[track] != '\0'){
        while(!is_empty(stack) && top(stack) != '(' && checkPriority(input[track]) <= checkPriority(top(stack))) {
            if(top(stack) != '\0') 
                printf("%c", top(stack));
            pop(&stack);
        }
        if (input[track] != ')') {
            push(input[track], &stack);
        } else {
            while (!is_empty(stack) && top(stack) != '('){
                printf("%c", top(stack));
                pop(&stack);
            }
            if (!is_empty(stack) && top(stack) == '(') {
                pop(&stack);
            }
        }
        track++;
    }

    while(!is_empty(stack)){
        if(top(stack) != '\0') {
            printf("%c", top(stack));
        }
        pop(&stack);
    }
    printf("\n");
    return 0;
}