#include <stdio.h>

int main()
{
    int a;
    scanf("%d", & a);
    puts((a % 4 == 0 && a % 100 != 0 || a % 400 == 0) ? "YES" : "NO");
}