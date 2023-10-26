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
    input = (! ((uruu % 4 == 0 ? 0 : 1)) & (uruu % 100 == 0 ? 0 : 1)) | ! ((uruu % 400 == 0 ? 0 : 1));
    
    if(input % 4 == 0)
        
        if(uruu % 100 != 0)
            printf("YES\n");
        else
            
            if(input % 400 != 0)
                scanf("NO\n");
            else
                printf("YES\n");
    else
        printf("NO\n");
    
    return 0;
}