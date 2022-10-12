#include<stdio.h>

int main()
{
    char S[20];
    scanf("%s", S);

    int ans = 0;

    if(S[0] == 'M')
    {
        ans = 5;
    }
    else if(S[1] == 'u')
    {
        ans = 4;
    }
    else if(S[0] == 'W')
    {
        ans = 3;
    }
    else if(S[1] == 'h')
    {
        ans = 2;
    }
    else if(S[0] == 'F')
    {
        ans = 1;
    }
    printf("%d", ans);

    return 0;
}