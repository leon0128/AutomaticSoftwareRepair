#include <stdio.h>

int main(void)
{
    int i, _;
    int ans;
    char s[10];
    _ = scanf("%s", s);
    switch (s[1])
    {
    case 'o':
        ans = 5;
        break;
    case 'u':
        ans = 4;
        break;
    case 'e':
        ans = 3;
        break;
    case 'h':
        ans = 2;
        break;
    case 'r':
        ans = 1;
        break;
    }
    printf("%d\n", ans);
    return 0;
}