#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef char firstName[50];
typedef char lastName[50];

// ノードの構造体
typedef struct name_tag {
    firstName firstName; // ノードに格納するFirstName
    lastName lastName; // ノードに格納するLastName
    struct name_tag *next; // 次のノードへのポインタ
} name_tag;

int main(){
    FILE *fptr;
    fptr = fopen("input2.txt", "r");
    if (fptr == NULL) {
        printf("Unable to open file\n");
        return -1;
    }

    name_tag *head = NULL, *temp = NULL;
    firstName first;
    lastName last;

    while(fscanf(fptr, "%49s %49s", first, last) == 2){ // ファイルから名前を読み込む
        name_tag *newNode = (name_tag *)malloc(sizeof(name_tag)); // 新しいノードを作成
        if (newNode == NULL) {
            printf("Unable to allocate memory\n");
            return -1;
        }
        strcpy(newNode->firstName, first); // ノードにfirstNameを格納
        strcpy(newNode->lastName, last); // ノードにlastNameを格納
        newNode->next = NULL; // 新しいノードの次のノードをNULLに設定

        if(head == NULL || strcmp(newNode->lastName, head->lastName) < 0){ // ノードが先頭に追加される場合
            newNode->next = head; // 新しいノードの次のノードをheadに設定
            head = newNode; // headを新しいノードに設定
        } else { // ノードが先頭以外に追加される場合
            temp = head;
            while(temp->next != NULL && strcmp(newNode->lastName, temp->next->lastName) > 0){ // ノードの位置を検索
                temp = temp->next; // 次のノードへ移動
            }
            newNode->next = temp->next; // 新しいノードの次のノードをtemp->nextに設定
            temp->next = newNode; // tempの次のノードを新しいノードに設定
        }
    }
    fclose(fptr);
    printf("線形リストの各要素が Last Name の辞書順を先頭から順に出力する\n");
    printf("--------------------------------------------------------\n");
    temp = head;
    while(temp != NULL){ // リストの要素を出力
        printf("苗字: %10s, 名前: %10s\n", temp->lastName, temp->firstName);
        temp = temp->next;
    }
    printf("\n");

    name_tag *headOfFirstName = NULL, *temp2 = NULL; // First Name の辞書順に並び替えるためのリスト

    temp = head;
    while (temp != NULL) { // First Name の辞書順に並び替える
        name_tag *newNode = (name_tag *)malloc(sizeof(name_tag));
        if (newNode == NULL) {
            printf("Unable to allocate memory\n");
            return -1;
        }
        strcpy(newNode->firstName, temp->firstName); // ノードにfirstNameを格納
        strcpy(newNode->lastName, temp->lastName); // ノードにlastNameを格納
        newNode->next = NULL;
        if(headOfFirstName == NULL || strcmp(newNode->firstName, headOfFirstName->firstName) < 0){ // ノードが先頭に追加される場合
            newNode->next = headOfFirstName;
            headOfFirstName = newNode;
        } else { // ノードが先頭以外に追加される場合
            temp2 = headOfFirstName;
            while (temp2->next != NULL && strcmp(newNode->firstName, temp2->next->firstName) > 0){
                temp2 = temp2->next;
            }
            newNode->next = temp2->next;
            temp2->next = newNode;
        }
        temp = temp->next;
    }

    printf("線形リストの各要素が First Name の辞書順を先頭から順に出力する\n"); // First Name の辞書順に並び替えたリストを出力
    printf("--------------------------------------------------------\n");
    temp2 = headOfFirstName;
    while(temp2 != NULL) { // リストの要素を出力
        printf("苗字: %10s, 名前: %10s\n", temp2->lastName, temp2->firstName);
        temp2 = temp2->next;
    }

    while (head != NULL) { // メモリの解放
        temp = head;
        head = head->next;
        free(temp);
    }

    while(headOfFirstName != NULL){ // メモリの解放
        temp2 = headOfFirstName;
        headOfFirstName = headOfFirstName->next;
        free(temp2);
    }

    return 0;
}