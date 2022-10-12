#include<stdio.h>
int main(void)
{
    int n;
    char a[100];
    a[0]=getchar();
    n=0;
    while(a[n]!='\n'){
        n++;
        a[n]=getchar();
    }
    printf("%c",a[n/2]);
    return 0;
}