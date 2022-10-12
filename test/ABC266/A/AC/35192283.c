#include<stdio.h>
#include<string.h>
int main()
{
    char str[100];
    scanf("%s",&str);
    int len = strlen(str);
    printf("%c\n",str[len/2]);




    return 0;
}
