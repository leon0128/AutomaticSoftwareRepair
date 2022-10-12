#include<stdio.h>
int main()
{
    int a, b;
    scanf("%d %d", &a, &b);
    if( a+b >= 7)
        printf("7\n");
    else
        printf("%d\n", a+b);
    return 0;
}