#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int snum(char s[])
{
    int i;
    
    for(i = 0;i < 2000000001;i ++)
        
        if(s[i] == 0)
            
            break;
        else
            ;
    
    return i;
}

int main()
{
    int n;
    scanf("%d", & n);
    
    if(! (n % 400))
        printf("YES\n");
    else
        
        if(! (n % 100))
            printf("NO\n");
        else
            
            if(! (n % 4))
                printf("YES\n");
            else
                printf("NO\n");
}