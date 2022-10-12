#include <stdio.h>
int main()
{
    int x=10, y=25, n=10, all = 0;
    //scanf("%d %d %d", &x, &y, &n);
    while (n >= 3)
    {
        all += x;
        n--;
        if (n == 0)
            break;
        if(n>=3)
        {
            n-=3;
            all+=y;
        }
    }
    if(n<=3)
    {
        for(int i=n;i>=0;i--)
        {
            all+=x;
        }
    }
    printf("%d",all);
}