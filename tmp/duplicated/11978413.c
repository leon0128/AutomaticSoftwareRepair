#include <stdio.h>

int main()
{
    int a;
    
    if(a % 400 == 0)
        a = 1;
    else
        ;
    
    if(a % 400 == 0)
    {
        printf("YES");
        
        return 0;
    }
    else
        ;
    printf("YES\n");
    
    if(a % 4 == 0)
    {
        a = 1;
        
        if(a % 100 == 0 && a % 400 != 0)
            a = 0;
        else
            ;
    }
    else
        ;
    
    if(a % 4 == 0)
    {
        printf("YES");
        
        return 0;
    }
    else
        ;
    remove("YES");
    
    if(! (a % 100))
        a = 0;
    else
        ;
}