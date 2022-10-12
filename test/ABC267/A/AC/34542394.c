#include <stdio.h>
#include <stdlib.h>

int main(void){
    char S[10];
    scanf("%s",S);

    switch(S[0]){
        case 'M':
        printf("5\n");
        break;
        case 'T':
        if(S[1]=='u') printf("4\n");
        else printf("2\n");
        break;
        case 'W':
        printf("3\n");
        break;
        case 'F':
        printf("1\n");
        break;
        default:
        printf("0\n");
        break;
    }

    return 0;
}