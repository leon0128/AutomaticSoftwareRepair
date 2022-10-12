#include<stdio.h>
int main(){
    char c='a';
    char ar[100];
    int l=0;
    scanf("%c",&c);
    while(c!='\n'){
        ar[l]=c;
        scanf("%c",&c);
        l+=1;
    }
    printf("%c",ar[l/2]);



    
    return 0;
}