#include <stdio.h>
#include <string.h>
 
int main(void){
    char s[99];
    int len;
    scanf("%s", &s);
    len = strlen(s);
 
    printf("%c\n", s[len/2]);
}