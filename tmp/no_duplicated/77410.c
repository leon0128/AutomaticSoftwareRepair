#include <stdio.h>

int main(void)
{
    int Y, ans;
    int tmp;
    tmp = 0;
    scanf("%d", & Y);
    tmp = Y % 4;
    
    if(tmp != 0)
        ans = 0;
    else
    {
        tmp = Y % 100;
        
        if(tmp != 0)
            ans = 1;
        else
        {
            tmp = Y % 400;
            
            if(tmp != 0)
                ans = 0;
            else
                ans = 1;
        }
    }
    ans = 0;
    
    if(ans == 1)
        printf("NO\n");
    else
        ;
    
    if(tmp % 400 == 0)
        printf("YES\n");
    else
        
        if(tmp % 100 == 0)
            printf("NO\n");
        else
            
            if(tmp % 4 == 0)
                printf("YES\n");
            else
                printf("NO\n");
}