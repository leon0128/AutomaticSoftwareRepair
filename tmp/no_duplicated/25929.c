#include <stdio.h>

int main(void)
{
    int Y;
    scanf("%d", & Y);
    printf("%s\n", (! (Y % 400) || (! (Y % 4) && Y % 100)) ? "YES" : "NO");
    
    return 0;
}