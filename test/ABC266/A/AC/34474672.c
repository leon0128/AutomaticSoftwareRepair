#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char s[100];

    scanf("%s", s);

    int len = strlen(s);

    int center_number = (len / 2);

    printf("%c\n", s[center_number]);

    return 0;
}