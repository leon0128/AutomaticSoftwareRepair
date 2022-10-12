#include<stdio.h>
#include <string.h>
 
int main(void)
{
    char S[100]={"z"};
    scanf("%s", &S);
    int n=strlen(S);
    int MiddleNumber=(n+1)/2-1;
    printf("%c", S[MiddleNumber]);
 
    return 0;
}