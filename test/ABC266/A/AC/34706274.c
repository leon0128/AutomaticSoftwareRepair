#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(void){
    char s[100] ;
    scanf("%s",s);
    int n = strlen(s);
    n = n/2; 
    printf("%c\n",*(s+n));
}