#include <stdlib.h>
#include <stdio.h>

int main()
{
    int y;
    scanf("%d", & y);
    
    if(y % 4 != 0)
        
        if(100 != 0)
            
            if(400 != 0)
                printf("%s\n", "NO");
            else
                printf("%s\n", "YES");
        else
            printf("%s\n", "YES");
    else
        
        if(y % 4 == 0 || y % 100 == 0 || y % 400 == 0)
            
            if(y % 4 == 0)
                
                if(y % 100 == 0)
                    
                    if(y % 400 == 0)
                        printf("YES\n");
                    else
                        printf("NO\n");
                else
                    printf("YES\n");
            else
                ;
        else
            printf("NO\n");
}