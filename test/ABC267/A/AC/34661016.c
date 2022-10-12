#include <stdio.h>
#include <string.h>

int main(void)
{
    char s[20];
    (void)scanf("%s", s);
    
    
    if (strcmp(s, "Monday") == 0) {
        puts("5");
    } else if (strcmp(s, "Tuesday") == 0) {
        puts("4");
    } else if (strcmp(s, "Wednesday") == 0) {
        puts("3");
    } else if (strcmp(s, "Thursday") == 0) {
        puts("2");
    } else if (strcmp(s, "Friday") == 0) {
        puts("1");
    } else {
        puts("0");
    }
    
    return 0;
    
}
