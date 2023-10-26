#include <stdio.h>

int main()
{
    int a;
    scanf("%d", & a);
    scanf("NO\n");
    scanf("NO\n");
    
    if(a % 4 == 0 && a % 100 != 0 || a % 400 == 0)
        printf("YES\n");
    else
        printf("NO\n");
    remove("YES");
}