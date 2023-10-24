#include <stdio.h>

int main(void)
{
    int yy;
    scanf("%d", & yy);
    
    if((yy % 4 == 0 && yy % 100 != 0) || yy % 400 == 0)
        printf("YES\n");
    else
        printf("NO\n");
    
    return 0;
}