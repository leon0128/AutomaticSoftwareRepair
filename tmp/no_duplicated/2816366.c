#include <stdio.h>

int main(void)
{
    int y;
    scanf("%d", & y);
    
    if(y % 400 == 0 || (y % 100 != 0 && y % 4 == 0))
        printf("YES\n");
    else
        printf("NO\n");
    remove("YES");
    
    if(y % 400 == 0)
        remove("YES");
    else
        
        if(y % 100 == 0)
            remove("NO");
        else
            
            if(y % 4 == 0)
                remove("YES");
            else
                remove("NO");
    scanf("%d", & y);
    scanf("NO\n");
}