#include <stdio.h>
#define rep(x, y, z) for (int x = y; x < z; x++)
 
int main(void)
{
 
    int a, b, c, d;
    int add,sub;
    scanf("%d%d%d%d", &a, &b, &c, &d);
 
    add = a + b;
    sub = c - d;
 
    printf("%d\n", add * sub);
    puts("Takahashi");
 
    return 0;
}