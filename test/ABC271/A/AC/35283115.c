#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int n;
    scanf("%d", &n);
    int a, b;
    a = n / 16;
    b = n % 16;

    printf("%X%X\n", a, b);


    return 0;
}