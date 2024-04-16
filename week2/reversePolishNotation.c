#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SIZE 256
#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define FAILURE 0

typedef char data_type;
typedef struct node_tag {
    data_type data;
    struct node_tag *next;
} node_type;

node_type *new_node(data_type x, node_type *p) {
    node_type *temp;
    temp = (node_type *)malloc(sizeof(node_type));
    if (temp == NULL) return NULL;
    temp->data = x;
    temp->next = p;
    return temp;
}

void initialize(node_type **pp){
    *pp = NULL;
}

void printList(node_type *head){
    node_type *current = head;
    while(current != NULL){
        printf("%c", current->data);
        if (current -> next != NULL)
            printf(" ");
        else
            printf("\n");
        current = current->next;
    }
}

int is_empty(node_type *p){
    if (p == NULL) return TRUE;
    else return FALSE;
}

int push(data_type x, node_type **pp){
    node_type *temp;
    temp = new_node(x, *pp);
    if (temp != NULL){
        *pp = temp;
        printList(*pp);
        return SUCCESS;
    } else {
        return FAILURE;
    }
}

int pop(node_type **pp)
{
    node_type *temp;

    if (*pp != NULL){
        temp = (*pp)->next;
        free(*pp);
        *pp = temp;
        printList(*pp);
        return SUCCESS;
    } else {
        return FAILURE;
    }
}

data_type top(node_type *p){
    if (p == NULL){
        if (p == NULL) return '\0';
        else return p->data;
    }
}

node_type *stack;

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
    char str[SIZE];
    scanf("%s", str);
    int i = 0;
    int priority;

    while (i <= strlen(str)){
        while (stack != NULL && top(stack) != '(' && (checkPriority(str[i]) <=  checkPriority(top(stack)))){
            printf("%c", top(stack));
            pop(&stack);
        }
        {
            /* code */
        }
        
    }

    return 0;
}