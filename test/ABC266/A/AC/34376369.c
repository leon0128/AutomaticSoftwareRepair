#include<stdio.h>
#include<string.h>
#include<limits.h>

#define long long ll

int main(void)
{
    char str[100];
    scanf("%s",str);

    int len = strlen(str);
    printf("%c",str[len/2]);

    return 0;
}