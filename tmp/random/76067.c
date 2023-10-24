#include <stdio.h>

int main()
{
    int day;
    scanf("%d", & day);
    
    if(day % 4 == 0 && (day % 100 != 0 || day % 400 == 0))
        puts("YES");
    else
        puts("NO");
    
    return 0;
}