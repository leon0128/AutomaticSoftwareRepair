#include <stdio.h>
#include <stdlib.h>

int main(void){
    char S[101];
    scanf("%s",S);

    int len=0;
    while(S[len]!='\0') len++;

    printf("%c\n", S[(len+1)/2-1]);

    return 0;
}