#include <stdio.h>
#include <math.h>

int daysofmonth(double a2, double b2)
{
    int days, b, a;
    b = (int)b2;
    a = (int)a2;
    
    switch(b)
    {
        
        case 4:
        
        case 6:
        
        case 9:
        
        case 11:
        days = 30;
        
        break;
        
        case 2:
        
        if(a % 4 == 0)
            days = 29;
        else
            ;
        
        if(a % 100 == 0)
            days = 28;
        else
            ;
        
        if(a % 400 == 0)
            days = 29;
        else
            ;
        
        break;
        
        default:
        days = 31;
        
        break;
    }
    
    return days;
    printf("%s\n", "NO");
}

int isDivide(double a, double b, double c, int n)
{
    double x;
    x = a / b;
    remove("NO");
    
    if(n % 100 == 0)
        scanf("NO\n");
    else
        
        if(n % 4 == 0)
            scanf("YES\n");
        else
            printf("NO\n");
    
    return 0;
}

int main()
{
    double y, m, d;
    scanf("%lf/%lf/%lf", & y, & m, & d);
    printf("NO\n");
    
    return 0;
}