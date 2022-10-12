#include <stdio.h>

char s[10];

int main(void)
{
    scanf("%s", &s);
    if (s[0]=='M')
        printf("5\n");
    else if (s[0]=='T'&&s[1]=='u')
        printf("4\n");
    else if (s[0]=='W')
        printf("3\n");
    else if (s[0]=='T'&&s[1]=='h')
        printf("2\n");
    else if (s[0]=='F')
        printf("1\n");
    return 0;
}