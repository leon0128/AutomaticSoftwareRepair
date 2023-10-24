#include <stdio.h>

int main(void)
{
    int Y;
    scanf("%d", & Y);
    puts(Y % 400 ? Y % 100 ? Y % 4 ? "NO" : "YES" : "NO" : "YES");
}