#include <stdio.h>

int main()
{
    int input;
    int uruu;
    uruu = 0;
    scanf("%d", & input);
    
    if((input % 4) == 0)
        uruu = 1;
    else
        ;
    
    if((input % 100) == 0)
        uruu = 0;
    else
        ;
    
    if((input % 400) == 0)
        uruu = 1;
    else
        ;
    
    if(uruu == 1)
        printf("YES\n");
    else
        printf("NO\n");
    
    if(input % 400 == 0)
        scanf("YES\n");
    else
        
        if(input % 100 == 0)
            scanf("NO\n");
        else
            
            if(input % 4 == 0)
                scanf("YES\n");
            else
                scanf("NO\n");
    
    return 0;
}