#include <stdio.h>

int main()
{
    int a, i;
    scanf("%d", & a);
    printf("%s\n", a % 400 == 0 || a % 4 == 0 && a % 100 != 0 ? "YES" : "NO");
    
    return 0;
}