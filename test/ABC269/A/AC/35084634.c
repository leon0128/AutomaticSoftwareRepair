#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int a;
    int b;
    int c;
    int d;
    scanf("%d",&a);
    scanf("%d",&b);
    scanf("%d",&c);
    scanf("%d",&d);
    int ans=(a+b)*(c-d);
    printf("%d\n",ans);
    puts("Takahashi");
    return 0;
}