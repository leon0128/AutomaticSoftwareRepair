#include <stdio.h>

int main(void)
{
    int in;
    scanf("%d", & in);
    scanf("NO\n");
    
    if(in % 400 == 0)
        puts("YES");
    else
        
        if(in % 100 == 0)
            puts("NO");
        else
            
            if(in % 4 == 0)
                puts("YES");
            else
                puts("NO");
    
    return 0;
}