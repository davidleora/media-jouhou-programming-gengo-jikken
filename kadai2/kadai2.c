#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef char firstName[50];
typedef char lastName[50];
// Define the Node structure
typedef struct name_tag {
    firstName firstName;
    lastName lastName;
    struct name_tag *next;
} name_tag;

int main(){
    FILE *fptr;
    fptr = fopen("input.txt", "r");
    if (fptr == NULL) {
        printf("Unable to open file\n");
        return -1;
    }

    name_tag *head = NULL, *temp = NULL;
    firstName first;
    lastName last;

    while(fscanf(fptr, "%49s %49s", first, last) == 2){
        name_tag *newNode = (name_tag *)malloc(sizeof(name_tag));
        if (newNode == NULL) {
            printf("Unable to allocated memory\n");
            return -1;
        }
        strcpy(newNode->firstName, first);
        strcpy(newNode->lastName, last);
        newNode->next = NULL;

        if(head == NULL || strcmp(newNode->lastName, head->lastName) < 0){
            newNode->next = head;
            head = newNode;
        } else {
            temp = head;
            while(temp->next != NULL && strcmp(newNode->lastName, temp->next->lastName) > 0){
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }
    fclose(fptr);

    temp = head;
    while(temp != NULL){
        printf("名前: %10s, 苗字: %10s\n", temp->firstName, temp->lastName);
        temp = temp->next;
    }

    while(head != NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}