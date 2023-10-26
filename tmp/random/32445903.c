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
    
    if(Y % 4 == 0 && (Y % 100 != 0 || Y % 400 == 0))
        printf("YES\n");
    else
        printf("NO\n");
    
    return 0;
}