#include<stdio.h>
#include<string.h>

int main(void){
    char moji[99];
    int i=0;
    scanf("%s",moji);
    i = strlen(moji);
    i = i/2;
    printf("%c",moji[i]);
    return 0;
}