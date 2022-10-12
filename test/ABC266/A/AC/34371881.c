#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void){
    char s[100];
    int n;
    scanf("%s", s);
    n = strlen(s);
    n = (n+1) / 2;
    printf("%c", s[n-1]);
}