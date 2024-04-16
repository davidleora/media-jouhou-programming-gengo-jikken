// プログラミング言語実験・C 言語 第1回課題レポート
// 学籍番号：2210745
// 氏名：LEORA DAVID
// 第１回課題・課題２

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef char firstName[50];
typedef char lastName[50];
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
            printf("Unable to allocate memory\n");
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
    printf("線形リストの各要素が Last Name の辞書順を先頭から順に出力する\n");
    printf("--------------------------------------------------------\n");
    temp = head;
    while(temp != NULL){
        printf("苗字: %10s, 名前: %10s\n", temp->lastName, temp->firstName);
        temp = temp->next;
    }
    printf("\n");

    name_tag *headOfFirstName = NULL, *temp2 = NULL;

    temp = head;
    while (temp != NULL) {
        name_tag *newNode = (name_tag *)malloc(sizeof(name_tag));
        if (newNode == NULL) {
            printf("Unable to allocate memory\n");
            return -1;
        }
        strcpy(newNode->firstName, temp->firstName);
        strcpy(newNode->lastName, temp->lastName);
        newNode->next = NULL;
        if(headOfFirstName == NULL || strcmp(newNode->firstName, headOfFirstName->firstName) < 0){
            newNode->next = headOfFirstName;
            headOfFirstName = newNode;
        } else {
            temp2 = headOfFirstName;
            while (temp2->next != NULL && strcmp(newNode->firstName, temp2->next->firstName) > 0){
                temp2 = temp2->next;
            }
            newNode->next = temp2->next;
            temp2->next = newNode;
        }
        temp = temp->next;
    }

    printf("線形リストの各要素が First Name の辞書順を先頭から順に出力する\n");
    printf("--------------------------------------------------------\n");
    temp2 = headOfFirstName;
    while(temp2 != NULL) {
        printf("名前: %10s, 苗字: %10s\n", temp2->firstName, temp2->lastName);
        temp2 = temp2->next;
    }

    // Free memory at last part
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    while(headOfFirstName != NULL){
        temp2 = headOfFirstName;
        headOfFirstName = headOfFirstName->next;
        free(temp2);
    }

    return 0;
}