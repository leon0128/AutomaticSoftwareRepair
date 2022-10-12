#include<stdio.h>
int main(void){
    char S[100];
    int b=0;
    int T;
    scanf("%s",S);
    for(int a=0;a<100;a++){
        if(S[a]=='\0'){
            b=a-1;
            T=(b+1)/2;
            break;
        }
    }
    printf("%c",S[T]);
    return 0;
}