#include <stdio.h>

int main()
{
    int Y;
    scanf("%d", & Y);
    
    if(Y % 4 == 0 && (Y % 100 != 0 || Y % 400 == 0))
        puts("YES");
    else
        puts("NO");
    
    return 0;
}