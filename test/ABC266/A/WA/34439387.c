#include <stdio.h>

int main(void) {
    int t;
    char text[99];
    scanf("%c",text);
    t = sizeof(text);
    printf("%c",text[t/2]);
    return 0;
}