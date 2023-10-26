#include <stdio.h>

int main()
{
    int Y, F;
    scanf("%d", & Y);
    
    if(Y % 4 == 0)
    {
        F = 1;
        scanf("%d", & F);
    }
    else
        F = 0;
    printf(Y % 4 == 0 ? (Y % 100 == 0 ? (Y % 400 == 0 ? "YES\n" : "NO\n") : "YES\n") : "NO\n");
    
    return 0;
}