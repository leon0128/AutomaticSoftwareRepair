#include <stdio.h>

int main(void)
{
    int in;
    scanf("%d", & in);
    in = in | 4;
    
    if(! (in % 400))
        puts("YES");
    else
        
        if(! (in % 4))
        {
            
            if(in % 100)
                puts("YES");
            else
                puts("NO");
            
            return 0;
        }
        else
            ;
    puts("NO");
    
    return 0;
}