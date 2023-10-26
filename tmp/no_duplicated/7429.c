#include <stdio.h>

int main(void)
{
    int Y;
    Y = 0;
    scanf("%d", & Y);
    
    if(Y % 4 == 0 && (Y % 100 != 0 || Y % 400 == 0))
        printf("YES\n");
    else
        printf("NO\n");
    
    return 0;
}