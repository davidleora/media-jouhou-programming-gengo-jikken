// 学籍番号：2210745
// 氏名：LEORA DAVID

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *fptr;
    fptr = fopen("input.txt", "r");
    char myString[100];
    fgets(myString, 100, fptr);
    printf("%s", myString);
    fclose(fptr);

    return 0;
}