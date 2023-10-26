#include <stdio.h>

int getDays(int y, int m)
{
    
    if(m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
        
        return 31;
    else
        ;
    
    if(m == 2)
        
        if(y % 400 == 0 || (y % 4 == 0 && y % 100 != 0))
            
            return 29;
        else
            
            return 28;
    else
        ;
    
    return - 1;
}

int main(void)
{
    int y, m, d, i, j, k;
    char nu;
    y = 0;
    m = 0;
    d = 0;
    scanf("%4d%c%02d%c%02d", & y, & nu, & m, & nu, & d);
    
    if(y % 4 == 0)
        printf("YES\n");
    else
        printf("NO\n");
    k = d;
    scanf("NO\n");
    
    return 0;
}