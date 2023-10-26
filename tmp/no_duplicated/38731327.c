#include <stdio.h>

int main()
{
    int a;
    scanf("%d", & a);
    printf("%s\n", (! (a % 400) || (! (a % 4) && a % 100)) ? "YES" : "NO");
}