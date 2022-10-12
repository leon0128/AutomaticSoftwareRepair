#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main(void){
    int N,num=0,sum=0;
    char change[17]="0123456789ABCDEF";
    char ans[17];
    scanf("%d",&N);
    num=N;
    strcpy(ans,change);
    printf("%c%c",ans[num/16],ans[num%16]);
    return 0;
}
