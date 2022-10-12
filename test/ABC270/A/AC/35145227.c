#include <stdio.h>

int main(void)
{
    int a, b;
    scanf("%i %i", &a, &b);
    if (a == 7 || b == 7 || a + b == 7)
    {
        printf("7\n");
    }
    else if ((a == 1 || a == 2 || a == 4) && (b == 1 || b == 2 || b == 4))
    {
        if (a == b)
        {
            printf("%i\n", a);
            return 0;
        }
        printf("%i\n", a + b);
    }
    else if(a + b < 7 || (a + b == 8 && (a == 6 || b == 6))) 
    {
        if (a >= b)
            printf("%i\n", a);
        else
            printf("%i\n", b);
    }
    else
    {
        printf("%i\n", 7);
    }
}