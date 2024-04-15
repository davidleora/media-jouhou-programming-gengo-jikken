// プログラミング言語実験・C 言語 第1回課題レポート
// 学籍番号：2210745
// 氏名：LEORA DAVID
// 第１回課題・課題１A・a

// データの個数が既知の場合、データとしてリスト構造をもたない、単なる配列を使用する。
// A.a は、データの入力順に総和を求めるプログラムである。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *fptr;
    int n = 21;
    double myArray[21] = {0.0};
    double sum = 0.0;
    fptr = fopen("input.txt", "r");

    for(int i = 0; i < 21; i++){
        fscanf(fptr, "%lf", &myArray[i]);
        sum += myArray[i];
    }
    
    for(int i = 0; i < 21; i++){
        printf("%lf\n", myArray[i]);
    }
    fclose(fptr);
    printf("The sum of the numbers is: %lf\n", sum);
    return 0;
}