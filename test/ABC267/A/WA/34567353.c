#include <string.h>
#include <stdio.h>
 
int main(void)
{
  	char days[10];
  	char *ans;
 
  	ans = fgets(days, 20, stdin);
    if (strcmp(ans, "Monday") == 0)
        printf("%d", 5);
    if (strcmp(ans, "Tuesday") == 0)
        printf("%d", 4);
    if (strcmp(ans, "Wednesday") == 0)
        printf("%d", 3);
    if (strcmp(ans, "Thursday") == 0)
        printf("%d", 2);
    if (strcmp(ans, "Friday") == 0)
        printf("%d", 1);
    return 0;
}