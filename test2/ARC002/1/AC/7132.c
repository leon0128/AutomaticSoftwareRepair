#include <stdio.h>

int main() {
int inp;
        scanf("%d", &inp);
        if (inp % 4 == 0) {
                if (inp % 400 == 0)
                        goto YES;
                else if (inp % 100 == 0)
                        goto NO;
                else
                        goto YES;
        }

NO:
        printf("NO\n");
        return 0;

YES:
        printf("YES\n");
        return 0;
}