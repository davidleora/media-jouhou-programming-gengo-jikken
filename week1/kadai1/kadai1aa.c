#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *fptr;
    int n = 21;
    double myArray[21] = {0.0};
    double sum = 0.0;
    fptr = fopen("input2.txt", "r"); // ファイルを読み込む

    for(int i = 0; i < 21; i++){
        fscanf(fptr, "%lf", &myArray[i]);
        sum += myArray[i];
    }
    
    printf("The numbers are:\n");
    printf("--------------------------\n");
    for(int i = 0; i < n; i++){
        printf("%25lf\n", myArray[i]);
    }
    printf("-------------------------- + \n");
    fclose(fptr);
    printf("Sum: %lf\n", sum); // 合計を出力
    return 0;
}