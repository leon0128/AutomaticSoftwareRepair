#include <stdio.h>

void hex (int num) {
    if (num < 10) {
        printf("%d", num);
    } else if (num == 10) {
        printf("A");
    } else if (num == 11) {
        printf("B");
    } else if (num == 12) {
        printf("C");
    } else if (num == 13) {
        printf("D");
    } else if (num == 14) {
        printf("E");
    } else if (num == 15) {
        printf("F");
    }
}

int main (void) {
    int n;
    scanf("%d", &n);
    
    int quotient = n / 16;
    int remainder = n % 16;
    hex(quotient);
    hex(remainder);
    printf("\n");

    return 0;
}