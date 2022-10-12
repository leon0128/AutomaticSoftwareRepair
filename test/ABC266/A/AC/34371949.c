#include <stdio.h>
#include <string.h>

int main()
{
    char s[99+1];
    int len;
    
    gets(s);
    
    len = strlen(s);
    
    printf("%c\n", s[len/2]);
    
    return 0;
}