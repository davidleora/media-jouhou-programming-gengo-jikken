// プログラミング言語実験・C 言語 第1回課題レポート
// 学籍番号：2210745
// 氏名：LEORA DAVID
// 第１回課題・課題１A・b

// データの個数が既知の場合、データとしてリスト構造をもたない、単なる配列を使用する。
// A.b は、データ入力後、絶対値に関して昇順に並べ替えたあとで総和を求めるプログラムである。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Function to swap elements
void swap(double *a, double *b){
    double t = *a;
    *a = *b;
    *b = t;
}

// Function to find the partition position
int partition(double arr[], int low, int high){
    double pivot = fabs(arr[high]); // Use absolute value for pivot
    int i = (low - 1);
    
    // Traverse each element of the array and compare them with the pivot
    for (int j = low; j < high; j++){
        if (fabs(arr[j]) < fabs(pivot)){
            // If element is smaller than pivot is found, swap it with the greater element pointed by i
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    // Swap the pivot element with the greater element
    swap(&arr[i+1], &arr[high]);
    return (i+1);
}

// Quick Sort function
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
    fptr = fopen("input.txt", "r");

    for(int i = 0; i < 21; i++){
        fscanf(fptr, "%lf", &myArray[i]);
    }

    quickSort(myArray, 0, n-1);

    for(int i = 0; i < n; i++){
        printf("%lf\n", myArray[i]);
        sum += myArray[i];
    } 
    fclose(fptr);
    printf("The sum of the numbers is: %lf\n", sum);
    return 0;
}