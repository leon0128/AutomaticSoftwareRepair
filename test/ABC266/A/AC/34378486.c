#include<stdio.h>
int main(){
    char s[100];
    int i=0;
    scanf("%s",s);
    while(s[i]!=NULL){
        i++;
    }
    printf("%c",s[i/2]);
    return 0;
}