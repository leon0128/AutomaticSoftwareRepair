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
    
    if(Y % 400 == 0)
        printf("YES\n");
    else
        
        if(Y % 4 == 0)
            
            if(Y % 100 != 0)
                printf("YES\n");
            else
                printf("NO\n");
        else
            printf("NO\n");
    scanf("YES\n");
    
    return 0;
}