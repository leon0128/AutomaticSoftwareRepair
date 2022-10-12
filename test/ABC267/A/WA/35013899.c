#include <stdio.h>

char s[10];

int main(void)
{
    scanf("%s", &s);
    if (s == "Monday")
        printf("5\n");
    else if (s == "Tuesday")
        printf("4\n");
    else if (s == "Wedneday")
        printf("3\n");
    else if (s == "Thursday")
        printf("2\n");
    else
        printf("1\n");
    return 0;
}