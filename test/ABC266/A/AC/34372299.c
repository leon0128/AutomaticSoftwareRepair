#include <stdio.h>
#include <string.h>

int main(void) {
    int n;
    char S[105];
    scanf("%s", S);
    n = strlen(S)/2;
    printf("%c", S[n]);
    return 0;
}
