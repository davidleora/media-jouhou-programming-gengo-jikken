// 学籍番号：2210745
// 氏名：LEORA DAVID

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *fptr;
    
    fptr = fopen("input.txt", "r");
    char myString[100];
    // fgets(myString, 100, fptr);
    // The first parameter specifies where to store the file content, which will be in the 'myString' array
    // The second parameter specifies the maximum size of data to read, which is myString(100)
    // The third parameter requires a file pointer that is used to read the file
    while(fgets(myString, 100, fptr)){
        printf("%s", myString);
    }
    fclose(fptr);

    return 0;
}