#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(void){
    char s[105];
    int n;
    
    scanf("%s", s);

    n = strlen(s);
    printf("%c", s[(n + 1)/2 -1]);
    
    return 0;
}