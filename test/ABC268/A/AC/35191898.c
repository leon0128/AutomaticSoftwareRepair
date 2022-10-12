#include <stdio.h>
int a[101];
int main()
{
    int n, ans = 0;
    for (int i = 0; i < 5; i++)
    {
        scanf("%d", &n);
        ans += !a[n];
        a[n]=1;
    }
    printf("%d",ans);
}