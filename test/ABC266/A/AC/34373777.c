#include<stdio.h>
#include<string.h>
int main()
{
    char ch[100];
    int i;
    scanf("%s",ch);
    printf("%c",ch[strlen(ch)/2]);

    return 0;
}
