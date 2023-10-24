#include <stdio.h>

int main(void)
{
    char input[4];
    int year;
    scanf("%d", & year);
    
    if((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0)))
        printf("YES\n");
    else
        printf("NO\n");
    fgets(input, 5, stdout);
}