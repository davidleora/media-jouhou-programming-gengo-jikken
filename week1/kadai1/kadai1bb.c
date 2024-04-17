#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef double data_type;
typedef struct node_tag {
    data_type data;
    struct node_tag *next;
} node_type;

void printList(node_type *head, double sum){
    node_type *current = head;
    while(current != NULL){
        sum += current->data;
        printf("%lf", current->data);
        if (current -> next != NULL)
            printf(" -> ");
        else
            printf("\n");
        current = current->next;
    }
    printf("The sum of the numbers is: %lf\n", sum);
}

int search_position(data_type x, node_type *p){
    int i = 0;
    while((p != NULL) && (fabs(x) > fabs(p->data))){
        p = p->next;
        i++;
    }
    return i;
}

int main(){
    FILE *fptr;
    int pos;
    double sum = 0.0;
    
    node_type *head = NULL;
    fptr = fopen("input2.txt", "r");

    data_type num;
    while(fscanf(fptr, "%lf", &num) != EOF){
        node_type *new_node = (node_type *)malloc(sizeof(node_type));
        new_node->data = num;
        new_node->next = NULL;

        pos = search_position(num, head);

        if (pos == 0 || head == NULL){
            new_node->next = head;
            head = new_node;
        } else {
            node_type *current = head;
            for(int i=0; i < pos-1 && current->next != NULL; i++){
                current = current->next;
            }
            new_node->next = current->next;
            current->next = new_node;
        }
    }
    printList(head, sum);
    fclose(fptr);
    return 0;
}