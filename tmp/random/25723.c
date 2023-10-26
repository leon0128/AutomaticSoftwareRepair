#include <stdio.h>

int main()
{
    int a;
    scanf("%d", & a);
    (a % 4) || (a % 100 == 0 && a % 400 != 0) ? printf("NO\n") : printf("YES\n");
    
    return 0;
}