#include<stdio.h>

int main(){
    int i;
    char s[100];

    scanf("%s", s);

     for(i=0;s[i]!='\0';i++);

     printf("%c", s[i / 2]);

     return 0;
}