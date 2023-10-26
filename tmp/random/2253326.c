#include <string.h>
#include <stdio.h>
#include <math.h>

int main()
{
    int y;
    scanf("%d", & y);
    puts(y % 400 ? y % 100 ? y % 4 ? "NO" : "YES" : "NO" : "YES");
    
    return 0;
}