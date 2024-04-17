#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// ２つの要素を入れ替える関数
void swap(double *a, double *b){
    double t = *a;
    *a = *b;
    *b = t;
}

// クイックソートのパーティション関数
int partition(double arr[], int low, int high){
    double pivot = fabs(arr[high]);
    int i = (low - 1);

    for (int j = low; j < high; j++){
        if (fabs(arr[j]) < fabs(pivot)){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[high]);
    return (i+1);
}

// クイックソート関数
void quickSort(double arr[], int low, int high){
    if (low < high){
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi-1);
        quickSort(arr, pi+1, high);
    }
}

int main(){
    FILE *fptr;
    int n = 21;
    double myArray[21] = {0.0};
    double sum = 0.0;
    fptr = fopen("input2.txt", "r"); // ファイルを読み込む

    for(int i = 0; i < 21; i++){
        fscanf(fptr, "%lf", &myArray[i]); // ファイルから数字を読み込む
    }

    quickSort(myArray, 0, n-1);

    printf("The numbers are:\n");
    printf("--------------------------\n");
    for(int i = 0; i < n; i++){
        printf("%25lf\n", myArray[i]); // ソートされた数字を出力
        sum += myArray[i];
    }
    printf("-------------------------- + \n");
    fclose(fptr);
    printf("Sum: %lf\n", sum); // 合計を出力
    return 0;
}