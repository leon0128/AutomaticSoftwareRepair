#include <stdio.h>

int main(void){
    int a, b, c, d;
    a = b = c = d = 0;
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);
    scanf("%d", &d);
    printf("%d\n", (a + b) * (c - d));
    printf("Takahashi\n");
    return 0;
}