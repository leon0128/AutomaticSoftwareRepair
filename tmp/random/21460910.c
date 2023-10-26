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
    printf("%s\n", b % 400 == 0 || a % 4 == 0 && a % 100 != 0 ? "YES" : "NO");
    
    return 0;
}