#include <stdio.h>

int main(void)
{
    int Y, ans;
    int tmp;
    tmp = 0;
    scanf("%d", & Y);
    
    if(Y % 4 != 0)
        printf("NO\n");
    else
        
        if(Y % 4 == 0 && Y % 100 != 0)
            printf("YES\n");
        else
            
            if(Y % 4 == 0 && Y % 100 == 0 && Y % 400 != 0)
                printf("NO\n");
            else
                printf("YES\n");
    
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
    
    return 0;
}