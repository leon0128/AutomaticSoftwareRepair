#include<stdio.h>
int main(void){
    char s[100];
    int i,x=0;

    scanf("%s",s);

    for(i=0; s[i]!='\0'; i++){
        x++;
    }
    x = x/2;
    printf("%c\n",s[x]);

    return 0;
}