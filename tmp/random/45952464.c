#include <stdio.h>

int main()
{
    int y, cnt;
    cnt = 0;
    scanf("%d", & y);
    
    if(y % 4 == 0)
        cnt = 1;
    else
        ;
    
    if(y % 100 == 0)
        cnt = 0;
    else
        ;
    
    if(y % 400 == 0)
        cnt = 1;
    else
        ;
    
    if(cnt % 100 == 0)
        printf("NO\n");
    else
        
        if(y % 4 == 0)
            printf("YES\n");
        else
            printf("NO\n");
    
    return 0;
}