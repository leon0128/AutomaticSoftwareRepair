#include<stdio.h>
#include<string.h>


int main(void)
{
    char str[100];
    int tr = 0;
    scanf("%s",str);

    if(str[0] == 'M')
    {
        tr = 5;
    }

    if(str[0] == 'T' && str[1] == 'u')
    {
        tr = 4;
    }

    if(str[0] == 'W')
    {
        tr = 3;
    }

    if(str[0] == 'T' && str[1] == 'h')
    {
        tr = 2;
    }

    if(str[0] == 'F')
    {
        tr = 1;
    }

    printf("%d",tr);

    return 0;
}