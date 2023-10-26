#include <stdio.h>

int main(void)
{
    char str[32];
    int n;
    fgets(str, sizeof (str), stdin);
    sscanf(str, "%d", & n);
    
    if(n % 400 == 0 || (n % 100 != 0 && n % 4 == 0))
        printf("YES\n");
    else
        printf("NO\n");
    
    return 0;
    
    if(n % 100 == 0)
        puts("NO");
    else
        ;
    
    return 0;
    
    if(n % 4 == 0)
        puts("YES");
    else
        ;
    
    return 0;
    puts("NO");
    
    return 0;
}