#include <stdio.h>
#include <string.h>
int main()
{
    char str[100];
    gets(str);
    int l=strlen(str);
    int index=l/2;
    printf("%c",str[index]);

   return 0;
}
