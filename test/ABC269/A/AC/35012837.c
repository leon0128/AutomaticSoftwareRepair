#include <stdio.h>

int a, b, c, d;
char s[] = "Takahashi";

int main(void)
{
    scanf("%d %d %d %d", &a, &b, &c, &d);
    printf("%d\n", (a+b)*(c-d));
    printf("%s\n", s);
    return 0;
}