#include <stdio.h>
int main()
{
    int a, b;
    scanf("%d%d", &a, &b);
    int p[] = { 4, 2, 1 };
    int mp1[10], mp2[10];
    mp1[a] = 1, mp2[b] = 1;
    for (int i = 0; i < 3; i++) {
        if (a >= p[i]) {
            a -= p[i];
            mp1[p[i]] = 1;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (b >= p[i]) {
            b -= p[i];
            mp2[p[i]] = 1;
        }
    }
    int ans = 0;
    if (mp1[1] == 1 || mp2[1] == 1)
        ans++;
    if (mp1[2] == 1 || mp2[2] == 1)
        ans += 2;
    if (mp1[4] == 1 || mp2[4] == 1)
        ans += 4;
    printf("%d\n", ans);
    return 0;
}
