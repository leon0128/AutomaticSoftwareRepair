#include<stdio.h>
int main()
{
    char zifu[200];
    int i=1;
    zifu[i]=getchar();
    while(zifu[i]!='\n')
    {
        i++;
        zifu[i]=getchar();
    }
    printf("%c",zifu[(i+1)/2]);
    return 0;
}