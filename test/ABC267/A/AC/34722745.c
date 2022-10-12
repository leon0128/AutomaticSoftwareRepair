#include<stdio.h>
int main()
{
    char s[20];
    scanf("%s",s);
    if (s[1]=='o')
    {
        printf("5");
    }
    else if (s[1]=='u')
    {
        printf("4");
    }
    else if (s[1]=='e')
    {
        printf("3");
    }
    else if (s[1]=='h')
    {
        printf("2");
    }
    else if (s[1]=='r')
    {
        printf("1");
    }
    return 0;
    
}