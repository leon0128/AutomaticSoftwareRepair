#include <stdio.h>
#include <stdlib.h>

int main()
{
    char ch;
    int d;
    ch=getchar();
    if (ch=='M')d=1;
    else if (ch=='W')d=3;
    else if (ch=='F')d=5;
    else if (ch=='T')
    {
        ch=getchar();
        if(ch=='u')d=2;
        else d=4;
    }
    printf("%d",6-d);
    return 0;
}