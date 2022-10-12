#include<stdio.h>
#include<string.h>

int main(void){
    size_t len;
    char str[99];
    scanf("%s",str);

    len=strlen(str);
    int len2=(len+1)/2;

    printf("%c\n",str[len2-1]);

    return 0;
}