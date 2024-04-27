#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define FAILURE 0

typedef int data_type;
typedef int freq_type;

// ノードの構造を定義するための構造体です。
typedef struct node_tag {
    data_type data;
    freq_type freq;
    struct node_tag *left;
    struct node_tag *right;
} node_type;

// 引数として与えられたノードのポインタをNULLに初期化します
void initialize(node_type **pp) {
    *pp = NULL;
}

// 指定された値が二分探索木に存在するかどうかを判定します
int is_member(data_type x, node_type *p) {
    if (p == NULL) return FALSE;
    else {
        if(x == p->data) return TRUE;
        else {
            if (x < p->data) return is_member(x, p->left);
            else return is_member(x, p->right);
        }
    }
}

// 与えられたノードの中で最小値を探します
data_type min(node_type *p) {
    while (p->left != NULL) {
        p = p->left;
    }
    return p->data;
}

// 新しいノードを作成します
node_type *new_node(data_type x) {
    node_type *temp = (node_type *)malloc(sizeof(node_type));
    if (temp == NULL) return NULL; // メモリが割り当てられなかった場合
    else {
        temp -> data = x; // データを設定
        temp -> freq = 1; // データの出現回数を設定
        temp -> left = NULL; // 左の子ノードをNULLに設定
        temp -> right = NULL; // 右の子ノードをNULLに設定
        return temp; // 新しいノードを返す
    }
}

// 二分探索木にデータを挿入します
int insert (data_type x, node_type **pp) {
    if (*pp == NULL) { // ノードが空の場合
        node_type *temp = new_node(x);
        if (temp == NULL) return FAILURE;
        *pp = temp;
        return SUCCESS;
    } else { // ノードが空でない場合
        if (x < (*pp)->data) return insert (x, &((*pp)->left)); // 左の子ノードに挿入
        else if (x > (*pp)->data) return insert(x, &((*pp)->right)); // 右の子ノードに挿入
        else {
            (*pp)->freq++; // 既に存在するデータの出現回数を増やす
            return SUCCESS;
        }
    }
}

// 二分探索木からデータを削除します
int delete (data_type x, node_type **pp) {
    if (*pp == NULL) return FAILURE; // ノードが空の場合
    else if (x < (*pp)->data) { // 左の子ノードを探索
        return delete(x, &((*pp)->left));
    } else if (x > (*pp)->data) { // 右の子ノードを探索
        return delete(x, &((*pp)->right));
    } else { // ノードが見つかった場合
        if ((*pp)->left == NULL && (*pp)->right == NULL) { // 子ノードがない場合
            free(*pp);
            *pp = NULL;
            return SUCCESS;
        } else if ((*pp)->left == NULL) { // 左の子ノードがない場合
            node_type *temp = *pp;
            *pp = (*pp)->right;
            free(temp);
            return SUCCESS;
        } else if ((*pp)->right == NULL) { // 右の子ノードがない場合
            node_type *temp = *pp;
            *pp = (*pp)->left;
            free(temp);
            return SUCCESS;
        } else { // 両方の子ノードがある場合
            (*pp)->data = min((*pp)->right); // 右の子ノードの最小値を取得
            return delete((*pp)->data, &((*pp)->right)); // 右の子ノードから最小値を削除
        }
    }
}

// 二分探索木を中順で出力します
void print_in_order(node_type *p) {
    if(p != NULL) { // ノードが空でない場合
        print_in_order(p->left);
        for (int i = 0; i < p->freq; i++){ // 出現回数分だけデータを出力
            printf("%d ", p->data); // データを出力
        }
        print_in_order(p->right); // 右の子ノードを探索
    }
}

// プログラム終了時に、動的に割り当てたメモリを開放する処理
void free_tree(node_type *p) {
    if (p != NULL) {
        free_tree(p->left); // 左の子ノードを開放
        free_tree(p->right); // 右の子ノードを開放
        free(p); // ノードを開放
    }
}

int main(){
    node_type *root; // 二分探索木のルートノード
    initialize(&root); // ルートノードを初期化
    int choice, x; // ユーザーの選択とデータを格納する変数

    while(TRUE) { // ユーザーが終了するまで繰り返す
        printf("\n1. Insert\n2. Delete\n3. Exit\nEnter your choice: "); 
        scanf("%d", &choice);

        switch(choice) {
            case 1: // 挿入
                printf("Enter the number to insert: ");
                scanf("%d", &x);
                if (insert(x, &root) == SUCCESS) {
                    printf("========================\nInsertion was successful\n");
                    printf("Tree contents: \n");
                    print_in_order(root);
                    printf("\n========================\n");
                } else {
                    printf("Insertion failed\n");
                }
                break;
            case 2: // 削除
                printf("Enter the number to delete: ");
                scanf("%d", &x);
                int result = delete(x, &root);
                if (delete(x, &root) == SUCCESS) {
                    printf("========================\nDeletion was successful\n");
                    printf("Tree contents: \n");
                    print_in_order(root);
                    printf("\n========================\n");
                } else if (result == FAILURE) {
                    printf("NUMBER NOT FOUND\n");
                } else {
                    printf("Deletion failed\n");
                }
                break;
            case 3: // 終了
                printf("========================\nExiting the program.\n========================\n");
                free_tree(root);
                return 0;
            default: // 1, 2, 3 以外の場合
                printf("Invalid choice. Please enter 1, 2, or 3.\n");
        }
    }
}