#include <stdio.h>

int main(void)
{
    int n;
    scanf("%d", & n);
    printf("%s\n", (! (n % 400) || (! (n % 4) && n % 100)) ? "YES" : "NO");
    
    return 0;
}