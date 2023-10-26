#include <stdio.h>

int main()
{
    int a, b;
    b = 1;
    scanf("%d", & a);
    
    if(a % 4 == 0)
        b = 0;
    else
        ;
    
    if(a % 100 == 0)
        b = 1;
    else
        ;
    
    if(a % 400 == 0)
        b = 0;
    else
        ;
    printf("%s\n", (((b % 400 == 0) ? 1 : (b % 100 == 0) ? 0 : (b % 4 == 0) ? 1 : 0) ? "YES" : "NO"));
    
    return 0;
}