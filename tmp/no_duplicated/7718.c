#include <stdio.h>

int main(void)
{
    int a;
    scanf("%d", & a);
    printf("%s\n", (((a % 400 == 0) ? 1 : (a % 100 == 0) ? 0 : (a % 4 == 0) ? 1 : 0) ? "YES" : "NO"));
    a = 0;
    
    return 0;
}