#include <stdio.h>

int main(void)
{
    int a;
    scanf("%d", & a);
    
    if((a % 4) == 0 && ((a % 100) != 0 || (a % 400) == 0))
        printf("YES");
    else
        printf("NO");
    puts("");
    
    return 0;
}