#include <string.h>
#include <stdio.h>
 
int main(void)
{
  	char days[20];
  	char *ans;
 
  	ans = fgets(days, 20, stdin);
    if (strcmp(ans, "Monday") == 0)
        printf("%d\n", 5);
    else if (strcmp(ans, "Tuesday") == 0)
        printf("%d\n", 4);
   　else if (strcmp(ans, "Wednesday") == 0)
        printf("%d\n", 3);
    else if (strcmp(ans, "Thursday") == 0)
        printf("%d\n", 2);
    else if (strcmp(ans, "Friday") == 0)
        printf("%d\n", 1);
    return 0;
}