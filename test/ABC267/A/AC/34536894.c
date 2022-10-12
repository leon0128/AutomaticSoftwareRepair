#include <stdio.h>
#include <string.h>
 
int main(void)
{
    char day;

    scanf("%*c%c", &day);

    switch (day)
    {
        case 'o': printf("5"); break;
        case 'u': printf("4"); break;
        case 'e': printf("3"); break;
        case 'h': printf("2"); break;
        case 'r': printf("1"); break;
    }

    return 0;
}