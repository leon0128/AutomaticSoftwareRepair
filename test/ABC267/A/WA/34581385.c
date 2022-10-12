#include <stdio.h>

int main(void) {

    char s[10];
    scanf("%s", s);

    if(strcmp(s, "Monday") == 0)
        puts("5");

    if(strcmp(s, "Tuesday") == 0)
        puts("4");

    if(strcmp(s, "Wednessday") == 0)
        puts("3");
    
    if(strcmp(s, "Thursday") == 0)
        puts("2");
    
    if(strcmp(s, "Friday") == 0)
        puts("1");

    return 0;
}