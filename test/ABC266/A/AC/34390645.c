#include <stdio.h>
#include <string.h>
int main()
{
    char s[100];
    int count=0;
    scanf("%s",s);

    count=strlen(s);


    printf("%.1s",s+count/2);
}
