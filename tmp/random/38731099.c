#include <stdio.h>

int main()
{
    int a;
    scanf("%d", & a);
    puts(a % 400 ? a % 100 ? a % 4 ? "NO" : "YES" : "NO" : "YES");
}