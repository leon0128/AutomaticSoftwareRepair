#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char s[124];
    scanf("%s", s);
    int t = strlen(s) / 2;
    printf("%c\n", s[t]);
    return 0;
}