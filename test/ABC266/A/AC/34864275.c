#include <stdio.h>
#include <string.h>

int main(void)
{

    char t[99];
    scanf("%s", t);

    printf("%c", t[strlen(t) / 2]);

    return 0;
}