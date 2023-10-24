#include <stdio.h>

int main()
{
    int Y;
    scanf("%d", & Y);
    (Y % 4) || (Y % 100 == 0 && Y % 400 != 0) ? printf("NO\n") : printf("YES\n");
    
    return 0;
}