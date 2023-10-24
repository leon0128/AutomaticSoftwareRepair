#include <stdio.h>

int main()
{
    int tmp;
    scanf("%d", & tmp);
    
    if((tmp % 400) == 0 || ((tmp % 4 == 0) && (tmp % 100) != 0))
        printf("YES\n");
    else
        printf("NO\n");
    
    return 0;
}