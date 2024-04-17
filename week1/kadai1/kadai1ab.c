#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void swap(double *a, double *b){
    double t = *a;
    *a = *b;
    *b = t;
}

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
    fptr = fopen("input1.txt", "r");

    for(int i = 0; i < 21; i++){
        fscanf(fptr, "%lf", &myArray[i]);
    }

    quickSort(myArray, 0, n-1);

    printf("The numbers are:\n");
    printf("--------------------------\n");
    for(int i = 0; i < n; i++){
        printf("%25lf\n", myArray[i]);
        sum += myArray[i];
    }
    printf("-------------------------- + \n");
    fclose(fptr);
    printf("Sum: %lf\n", sum);
    return 0;
}