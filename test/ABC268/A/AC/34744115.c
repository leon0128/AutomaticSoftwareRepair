#include<stdio.h>
#include<string.h>

int main(void)
{
    int a, b, c, d, e;
    scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);
    int i = 5;
    if (a == b || c == a || d == a || e == a)
    {
        i--;
    }
    
    if (b == c || b == d || b == e)
    {
        i--;
    }
    
    if (c == d || c == e)
    {
        i--;
    }
    
    if (d == e)
    {
        i--;
    }
    printf("%d\n", i);
}    