#include<stdio.h>
int main()
{
    int i=1,A,B,C,D,E;
    scanf("%d", &A);
    scanf("%d", &B);
    if(B!=A)
    {
        i++;
    }
    scanf("%d", &C);
    if(C!=B && C!=A)
    {
        i++;
    }
    scanf("%d", &D);
    if(D!=A && D!=B && D!=C)
    {
        i++;
    }
    scanf("%d", &E);
    if(E!=A && E!=B && E!=C && E!=D)
    {
        i++;
    }
    printf("%d", i);
    return 0;
}