#include<stdio.h>
#include<string.h>

int main(){
    char s[99];
    scanf("%s", s);
    int length = strlen(s)/2;
    printf("%c", s[length]);

    return 0;
}