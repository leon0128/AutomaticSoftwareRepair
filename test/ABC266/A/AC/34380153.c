#include <stdio.h>
#include <string.h>

int main()
{
    char S[100];
    int T,t;

    scanf("%s",S);

    T=strlen(S);
    t=(T+1)/2-1;

    printf("%c\n",S[t]);

    return 0;
}