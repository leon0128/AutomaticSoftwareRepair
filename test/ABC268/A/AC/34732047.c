#include <stdio.h>

int main(void)
{
    int map[102] = {0};

    for (int i = 0; i < 5; i += 1) {
        int tmp;
        scanf("%d", &tmp);
        map[tmp] += 1;
    }

    int ans = 0;
    for (int i = 0; i <= 100; i+= 1) {
        if (map[i] > 0) {
            ans += 1;
        }
    }

    printf("%d", ans);
    return 0;
}