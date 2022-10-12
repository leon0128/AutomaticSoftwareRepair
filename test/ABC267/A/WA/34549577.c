#include <string.h>
#include <stdio.h>

int main(void)
{
  	char days[20];
  	fgets(days, 20, stdin);
    if (strcmp(days, "Monday") == 0)
        printf("%d", 5);
    else if (strcmp(days, "Tuesday") == 0)
        printf("%d", 4);
    else if (strcmp(days, "Wednesday") == 0)
        printf("%d", 3);
    else if (strcmp(days, "Thursday") == 0)
        printf("%d", 2);
    else if (strcmp(days, "Friday") == 0)
        printf("%d", 1);
    return 0;
}