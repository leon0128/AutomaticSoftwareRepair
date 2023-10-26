#include <stdio.h>

int main(void)
{
    int in;
    scanf("%d", & in);
    
    if(! (in % 4) && (! (in % 400) || in % 100))
        printf("YES\n");
    else
        printf("NO\n");
    scanf("%d", & in);
    
    return 0;
}