#include <stdio.h>

int main() {
    int N;
    char res1, res2;

    scanf("%d", &N);

    if (N / 16 >= 10) {
        res1 = 'A' + N / 16 - 10;
    } else {
        res1 = '0' + N / 16;
    }

    if (N % 16 >= 10) {
        res2 = 'A' + N % 16 - 10;
    } else {
        res2 = '0' + N % 16;
    }

    printf("%c%c", res1, res2);
    return (0);
}