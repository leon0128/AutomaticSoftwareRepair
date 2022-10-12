#include <stdio.h>
#include <string.h>

int main(void){
    char s[1024];
    scanf("%s", s);
    int i = (strlen(s) - 1) / 2;
    printf("%c", s[i]);
}