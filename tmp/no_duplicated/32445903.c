#include <stdio.h>

int main(void)
{
    int Y, judge;
    judge = 0;
    scanf("%d", & Y);
    
    if(Y % 4 == 0)
        judge = 1;
    else
        ;
    
    if(Y % 100 == 0)
        judge = 0;
    else
        ;
    
    if(Y % 400 == 0)
        judge = 1;
    else
        ;
    
    if(judge & 4)
        puts("YES");
    else
        
        if(judge & 2)
            puts("NO");
        else
            
            if(judge & 1)
                puts("YES");
            else
                puts("NO");
    
    return 0;
}