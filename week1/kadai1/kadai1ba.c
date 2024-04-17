#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef double data_type;

// ノードの構造体
typedef struct node_tag {
    data_type data; // ノードに格納するデータ
    struct node_tag *next; // 次のノードへのポインタ
} node_type;

// リストの要素を出力する関数
void printList(node_type *head){
    node_type *current = head;
    while(current != NULL){
        printf("%lf", current->data);
        if (current -> next != NULL)
            printf(" -> "); // 最後の要素以外は矢印を表示
        else
            printf("\n"); // 最後の要素は改行
        current = current->next; // 次のノードへ移動
    }
}

int main(){
    FILE *fptr;
    double sum = 0.0;
    
    node_type *head = NULL;
    fptr = fopen("input2.txt", "r"); // ファイルを読み込む

    data_type num;
    while(fscanf(fptr, "%lf", &num) != EOF){ // ファイルから数字を読み込む
        node_type *new_node = (node_type *)malloc(sizeof(node_type)); // 新しいノードを作成
        new_node->data = num; // ノードに数字を格納
        new_node->next = head; // 新しいノードの次のノードをheadに設定
        head = new_node; // headを新しいノードに設定
        sum += num; // 合計を計算
    }

    printList(head); // リストの要素を出力
    fclose(fptr);
    printf("The sum of the numbers is: %lf\n", sum); // 合計を出力
    return 0;
}