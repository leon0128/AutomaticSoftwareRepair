#include <stdio.h>

int main(void)
{
    int Y;
    scanf("%d", & Y);
    printf(Y % 4 == 0 ? (Y % 100 == 0 ? (Y % 400 == 0 ? "YES\n" : "NO\n") : "YES\n") : "NO\n");
    
    return (0);
}