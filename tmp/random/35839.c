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
    scanf("%d", & input);
    
    return 0;
}