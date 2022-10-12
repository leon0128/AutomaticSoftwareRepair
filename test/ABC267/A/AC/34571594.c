#include <string.h>
#include <stdio.h>
 
int main(void)
{
  	char days[20];
  	char *ans;
 
  	ans = fgets(days, 20, stdin);
    if (strcmp(ans, "Monday\n") == 0)
        printf("%d\n", 5);
    else if (strcmp(ans, "Tuesday\n") == 0)
        printf("%d\n", 4);
   　else if (strcmp(ans, "Wednesday\n") == 0)
        printf("%d\n", 3);
    else if (strcmp(ans, "Thursday\n") == 0)
        printf("%d\n", 2);
    else if (strcmp(ans, "Friday\n") == 0)
        printf("%d\n", 1);
    return 0;
}