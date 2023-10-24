#include <stdio.h>

int main()
{
    int y;
    scanf("%d", & y);
    
    if(y % 4 == 0)
        printf("%s\n", y % 400 == 0 || y % 100 && y % 4 == 0 ? "YES" : "NO");
    else
        printf("NO\n");
    
    return 0;
}