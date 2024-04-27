#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100
#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define FAILURE 0

typedef char data_type;
typedef struct node_tag {
    data_type data;
    struct node_tag *next;
} node_type;

// スタックを初期化します
void initialize(node_type **pp){
    *pp = NULL; // スタックの先頭を NULL に設定します（空の状態にします）
}

// スタックが空かどうかを確認します
int is_empty(node_type *p){
    return (p == NULL) ? TRUE : FALSE;
}

// スタックの先頭にあるデータを取得します
data_type top(node_type *p){
    if (is_empty(p)){ // スタックが空の場合、NULL文字を返します
        printf("スタックは空です\n");
        return '\0'; 
    }
    return p->data; // 空出ない場合、先頭のデータを返します
}

// 新しいノードを作成し、スタックに追加します
node_type *new_node(data_type x, node_type *next) {
    node_type *temp = (node_type *)malloc(sizeof(node_type));
    if (temp != NULL) { // メモリの割り当てが成功した場合、データを設定し、次のノードを設定します
        temp->data = x;
        temp->next = next;
    }
    return temp;
}

// スタックにデータを追加します
int push(data_type x, node_type **pp){
    node_type *temp = new_node(x, *pp); // 新しいノードを作成します
    if (temp == NULL) return FAILURE;
    *pp = temp; // スタックの先頭を新しいノードに設定します
    return SUCCESS;
}

// スタックからデータをポップします
int pop(node_type **pp)
{
    node_type *temp;

    if (!is_empty(*pp)){ // スタックが空でない場合、先頭のノードを削除します
        temp = (*pp)->next; // 次のノードを一時的に保存します
        free(*pp); // 現在の先頭のノードを削除します
        *pp = temp; // スタックの先頭を次のノードに設定します
        return SUCCESS;
    }
    return FAILURE;
}

// 与えられた演算子の優先順位を返します
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

// 現在の文字が単項演算子かどうかを確認します
int isOperator(char previous, char current){
    // 前の文字が演算子または開き括弧であり、現在の文字が単項演算子の場合、TRUE を返します
    if ((previous == '=' || previous == '(' || previous == '+' || previous == '-' || previous == '*' || previous == '/') && (current == '-')) {
        return TRUE;
    } else return FALSE;
}

int main() {
    node_type *stack; // スタックを宣言します
    initialize(&stack); // スタックを初期化します
    char input[SIZE], previousChar = 0; // 入力文字列と前の文字を格納する変数を宣言します
    int track = 0; // 入力文字列の位置を追跡する変数を宣言します

    printf("式を入力してください：\n");
    fgets(input, SIZE, stdin); // 入力文字列を取得します
    int len = strlen(input); 
    if(input[len-1] == '\n') // 改行文字を削除します
        input[len-1] = '\0'; // NULL文字に置き換えます

    while (input[track] != '\0') { // 入力文字列の終わりに達するまで繰り返します
        if(input[track] == ' '){ // 空白文字をスキップします
            track++;
            continue;
        }

        if(isOperator(previousChar, input[track])){ // 単項演算子の判定を行います
            track++;
            push('-', &stack);
            push(input[track], &stack);
            previousChar = input[track]; // 前の文字を更新します
            track++;
            continue;
        }

        // スタックの先頭にある演算子の優先順位が現在の文字の優先順位よりも高い場合、スタックから演算子を取り出し、出力します
        while(!is_empty(stack) && top(stack) != '(' && checkPriority(input[track]) <= checkPriority(top(stack))) {
            printf("%c", top(stack));
            pop(&stack);
        }

        // 現在の文字が閉じ括弧の場合、開き括弧が見つかるまでスタックから演算子を取り出し、出力します
        if (input[track] != ')') {
            push(input[track], &stack);
        } 
        else { // 閉じ括弧が見つかった場合、開き括弧が見つかるまでスタックから演算子を取り出し、出力します
            while (!is_empty(stack) && top(stack) != '('){
                printf("%c", top(stack));
                pop(&stack);
            }
            if (!is_empty(stack) && top(stack) == '(') {
                pop(&stack);
            }
        }
        previousChar = input[track]; // 前の文字を更新します
        track++;
    }

    while(!is_empty(stack)){ // スタックに残っている演算子を取り出し、出力します
        if(top(stack) != '\0') {
            printf("%c", top(stack));
        }
        pop(&stack);
    }
    printf("\n");
    return 0;
}