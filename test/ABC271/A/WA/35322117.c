#include <stdio.h>
int main()
{
    int n;
    scanf("%d", &n);
    char a, b;
    a = (n %16)+'0';
    b = ((n/16) % 16)+'0';
    if (a >= '9')
    {
        a = a + 7;
    }
    if (b >= '9')
    {
        b = b + 7;
    }
    
    printf("%c%c", b, a);

    return 0;
}