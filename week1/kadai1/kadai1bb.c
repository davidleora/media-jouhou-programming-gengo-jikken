#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef double data_type;

// ノードの構造体
typedef struct node_tag {
    data_type data;
    struct node_tag *next;
} node_type;

// リストの要素を出力する関数
void printList(node_type *head, double sum){
    node_type *current = head;
    while(current != NULL){
        sum += current->data; // 合計を計算
        printf("%lf", current->data); // ノードのデータを出力
        if (current -> next != NULL)
            printf(" -> "); // 最後の要素以外は矢印を表示
        else
            printf("\n"); // 最後の要素は改行
        current = current->next; // 次のノードへ移動
    }
    printf("The sum of the numbers is: %lf\n", sum); // 合計を出力
}

// リストの要素を検索する関数
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
    while(fscanf(fptr, "%lf", &num) != EOF){ // ファイルから数字を読み込む
        node_type *new_node = (node_type *)malloc(sizeof(node_type)); // 新しいノードを作成
        new_node->data = num; // ノードに数字を格納
        new_node->next = NULL; // 新しいノードの次のノードをNULLに設定

        pos = search_position(num, head); // ノードの位置を検索

        if (pos == 0 || head == NULL){ // ノードが先頭に追加される場合
            new_node->next = head; // 新しいノードの次のノードをheadに設定
            head = new_node; // headを新しいノードに設定
        } else {
            node_type *current = head; // ノードの位置を検索
            for(int i=0; i < pos-1 && current->next != NULL; i++){ // ノードの位置を検索
                current = current->next;
            }
            new_node->next = current->next; // 新しいノードの次のノードをcurrentの次のノードに設定
            current->next = new_node; // currentの次のノードを新しいノードに設定
        }
    }
    printList(head, sum); // リストの要素を出力
    fclose(fptr);
    return 0;
}