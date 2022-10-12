#include <stdio.h>
#include <string.h>

int main(void) {
    char s[101];
    int len = 0;
    char ans;
    scanf("%s", s);
    len = (int)strlen(s);
    ans = s[len/2];
    printf("%c", ans);
    return 0;
}