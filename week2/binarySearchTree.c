#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define FAILURE 0

typedef int data_type;
typedef int freq_type;
typedef struct node_tag {
    data_type data;
    freq_type freq;
    struct node_tag *left;
    struct node_tag *right;
} node_type;

void initialize(node_type **pp) {
    *pp = NULL;
}

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

data_type min(node_type *p) {
    while (p->left != NULL) {
        p = p->left;
    }
    return p->data;
}

node_type *new_node(data_type x) {
    node_type *temp = (node_type *)malloc(sizeof(node_type));
    if (temp == NULL) return NULL;
    else {
        temp -> data = x;
        temp -> freq = 1;
        temp -> left = NULL;
        temp -> right = NULL;
        return temp;
    }
}

int insert (data_type x, node_type **pp) {
    if (*pp == NULL) {
        node_type *temp = new_node(x);
        if (temp == NULL) return FAILURE;
        *pp = temp;
        return SUCCESS;
    } else {
        if (x < (*pp)->data) return insert (x, &((*pp)->left));
        else if (x > (*pp)->data) return insert(x, &((*pp)->right));
        else {
            (*pp)->freq++;
            return SUCCESS;
        }
    }
}

/** 未実装：データの削除（予定）
int delete (data_type x, node_type **pp) {

}
**/

void print_in_order(node_type *p) {
    if(p != NULL) {
        print_in_order(p->left);
        for (int i = 0; i < p->freq; i++){
            printf("%d ", p->data);
        }
        print_in_order(p->right);
    }
}

// プログラム終了時に、動的に割り当てたメモリを開放する処理
void free_tree(node_type *p) {
    if (p != NULL) {
        free_tree(p->left);
        free_tree(p->right);
        free(p);
    }
}

int main(){
    node_type *root;
    initialize(&root);
    int choice, x;

    while(TRUE) {
        printf("\n数値を入力してください（プログラム修了：－１）：");
        scanf("%d", &x);
        if (x == -1) break;
        if (insert(x, &root) == SUCCESS) {
            printf("挿入が成功しました\n");
            printf("木の中身：");
            print_in_order(root);
            printf("\n");
        } else {
            printf("挿入が失敗しました\n");
        }
    }
    free_tree(root);
    printf("プログラムを終了します。\n");
    return 0;
}