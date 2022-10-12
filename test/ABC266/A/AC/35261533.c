#include <stdio.h>
#include <string.h>

int main() {
    char S[100];
    int N;

    scanf("%s", S);

    N = strlen(S);
    printf("%c\n", S[N / 2]);
    return(0);
}