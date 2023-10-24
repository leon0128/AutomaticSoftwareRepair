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
    
    if(cnt == 1)
        printf("YES");
    else
        printf("NO");
    printf("\n");
}