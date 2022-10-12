#include <stdio.h>

int main(void)
{
    char s[10];
    scanf("%s", &s);

    if (s[0] == 77) // 1文字目がM
        printf("5\n");

    else if (s[1] == 117)
        printf("4\n");

    else if (s[0] == 87)
        printf("3\n");

    else if (s[1] == 104)
        printf("2\n");

    else
        printf("1\n");

    return 0;
}