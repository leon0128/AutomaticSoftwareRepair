#include<stdio.h>
#include<string.h>

int main(){
    char str[100];
    scanf("%s", &str);
    printf("%c\n", str[strlen(str)/2]);
    return 0;
}