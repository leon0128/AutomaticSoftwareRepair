#include<stdio.h>

#include<string.h>

int main(){

    char str[100];

    gets(str);

    int length;

    length=strlen(str);

    length=length/2;

    printf("%c",str[length]);



return 0;

}
