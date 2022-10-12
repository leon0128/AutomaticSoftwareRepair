#include<stdio.h>
#include<string.h>

int main(void) {
    char *s;
    int len;

    scanf("%s", s);
    len = strlen(s);
    len /= 2;
    printf("%c\n", s[len]);
    return 0;
}