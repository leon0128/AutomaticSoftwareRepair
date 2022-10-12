#include <stdio.h>
#include <string.h>

int main(void) {
    int t;
    char text[99];
    scanf("%s",text);
    t = strlen(text);
    printf("%c",text[t/2]);
    return 0;
}