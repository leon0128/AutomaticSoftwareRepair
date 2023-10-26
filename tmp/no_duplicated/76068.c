#include <stdio.h>

int main()
{
    int day;
    scanf("%d", & day);
    
    if(day % 400 == 0 || (day % 100 != 0 && day % 4 == 0))
        printf("YES\n");
    else
        printf("NO\n");
    
    return 0;
}