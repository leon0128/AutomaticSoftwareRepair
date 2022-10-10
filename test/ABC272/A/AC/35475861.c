#include <stdio.h>

int main() {
    int input, sum = 0, i;
    scanf("%d" , &input);
    for(i = input; i >= 1; i--) {
        scanf("%d" , &input);
        sum += input;
    }
    printf("%d", sum);
}