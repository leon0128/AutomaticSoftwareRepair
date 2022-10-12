#include<stdio.h>
#include<string.h>
int main()
{
    char S[99];
    gets(S);
    int d=strlen(S);
    for(int i=0;i<d;i++)
    {
        if(i==d/2)
        {
            printf("%c",S[i]);
        }
    }
    return 0;
}