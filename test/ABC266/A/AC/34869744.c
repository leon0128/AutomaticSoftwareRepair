#include <stdio.h>

int main(void){
    char S[100];
    int i;

    scanf("%s",S);

    for (i=0; S[i]!='\0'; i++);

    char senter=S[((i+1)/2)-1];
    printf("%c",senter);
    
    return 0;
}