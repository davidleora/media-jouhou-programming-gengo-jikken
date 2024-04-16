// プログラミング言語実験・C 言語 第1回課題レポート
// 学籍番号：2210745
// 氏名：LEORA DAVID
// 第１回課題・課題１B・a

// データの個数が未知の場合、データとしてポインタによる線形リスト。
// B.a は、データの入力順に総和を求める。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef double data_type; // データの型
typedef struct node_tag {
    data_type data; // データ
    struct node_tag *next; // 次のノードへのポインタ
} node_type;

void printList(node_type *head){
    node_type *current = head;
    while(current != NULL){
        printf("%lf", current->data);
        if (current -> next != NULL)
            printf(" -> ");
        else
            printf("\n");
        current = current->next;
    }
}

int main(){
    FILE *fptr;
    double sum = 0.0;
    
    node_type *head = NULL;
    fptr = fopen("input.txt", "r");

    data_type num;
    while(fscanf(fptr, "%lf", &num) != EOF){
        node_type *new_node = (node_type *)malloc(sizeof(node_type));
        new_node->data = num;
        new_node->next = head;
        head = new_node;
        sum += num;
    }

    printList(head);

    fclose(fptr);
    printf("The sum of the numbers is: %lf\n", sum);
    return 0;
}