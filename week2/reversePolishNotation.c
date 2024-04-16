#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SIZE 256

int top = -1;
char stack[SIZE];
char output[SIZE] = "";
void wordParser(char *input);
void push(char n);
void pop();

int main(){
    char input[SIZE];
    printf("中置記法の算術式を入力してください：");
    fgets(input, SIZE, stdin);
    char *newline = strchr(input, '\n');
    if (newline) *newline = '\0';
    printf("入力された中置記法の算術式は %s です。\n", input);
    wordParser(input);
    return 0;
}

void wordParser(char *input){
    for (int i = 0; input[i] != '\0'; i++){
        printf("Character: %c\n", input[i]);
    }
}

void push(char n){
    if (top == SIZE - 1)
        printf("スタックがオーバーフローしました\n");
    else {
        top++;
        stack[top] = n;
    }
}

void pop(){
    if (top == -1)
        printf("スタックがアンダーフローしました\n");
    else
        strcat(output, stack[top--]);
}