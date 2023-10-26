#include <stdio.h>

int main()
{
    int a;
    scanf("%d", & a);
    printf("%s\n", (((a % 400 == 0) ? 1 : (a % 100 == 0) ? 0 : (a % 4 == 0) ? 1 : 0) ? "YES" : "NO"));
}