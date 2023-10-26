#include <stdio.h>

int main(void)
{
    char str[32];
    int n;
    fgets(str, sizeof (str), stdin);
    sscanf(str, "%d", & n);
    puts(n % 4 == 0 && (n % 100 != 0 || n % 400 == 0) ? "YES" : "NO");
    
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