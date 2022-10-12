#include <stdio.h>
#include <string.h>

int main()
{
    char s[16];
    int when;

    gets(s);
    
    if (strcmp(s, "Monday") == 0)
        when = 6 - 1;
    if (strcmp(s, "Tuesday") == 0)
        when = 6 - 2;
    if (strcmp(s, "Wednesday") == 0)
        when = 6 - 3;
    if (strcmp(s, "Thursday") == 0)
        when = 6 - 4;
    if (strcmp(s, "Friday") == 0)
        when = 6 - 5;
    if (strcmp(s, "Saturday") == 0)
        when = 6 - 6 + 7;
    if (strcmp(s, "Sunday") == 0)
        when = 6 - 7 + 7;

    printf("%d\n", when);

    return 0;
}