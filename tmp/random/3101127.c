#include <stdio.h>

int main(void)
{
    int n;
    scanf("%d", & n);
    puts(n % 400 ? n % 100 ? n % 4 ? "NO" : "YES" : "NO" : "YES");
    
    return 0;
}