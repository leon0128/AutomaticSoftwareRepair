#include <stdio.h>

int main(){
    int x, y, n;
    scanf("%d %d %d", &x, &y, &n);

    int a, b, ans1, ans2;

    ans1=n*x;

    a=(n%3);
    b=(n/3);

    ans2=(a*x) + ((b*y));

    if(ans1 <= ans2) printf("%d\n", ans1);
    else printf("%d\n", ans2);

    return 0;
}