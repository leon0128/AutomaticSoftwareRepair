#include <stdio.h>

int main(void) {
    int t;
    char text[99];
    scanf("%s",text);
    t = sizeof(text);
    printf("%c",text[t/2+1]);
    return 0;
}