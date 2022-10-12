#include <stdio.h>
#include <stdlib.h>
#define PT printf("%d",x)

int main()
{
    char a[100];
    int b,x;
    scanf("%s",&a);
    for(int i=0;; i++)
    {
        if (a[i]=='\0')
        {
            b=i;
            break;
        }
    }
    if(b==6)
    {
        if(a[0]=='M')
        {
            x=5;
            PT;
        }
        else
        {
            x=1;
            PT;
        }
    }
    if(b==7)
    {
        x=4;
        PT;
    }
    if(b==8)
    {
        x=2;
        PT;
    }
    if(b==9)
    {
        x=3;
        PT;
    }
    return 0;
}
