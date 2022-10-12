#include <stdio.h>
#include <string.h>
int main()
{
    char ch[100];
    scanf("%s",ch);
    int middle = (strlen(ch)+1)/2;
    printf("%c\n",ch[middle-1]);
    return 0;
}