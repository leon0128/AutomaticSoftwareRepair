#include <stdio.h>
#include <string.h>

int main() {
    char c[100];
    scanf("%s", c);
    printf("%c", c[strlen(c) / 2]);
    return 0;
}