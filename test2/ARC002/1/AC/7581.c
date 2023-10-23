#include <stdio.h>
int main(void) {
    int n;
    scanf("%d", &n);
    if (n % 4 == 0){
        if (n % 100 == 0) {
            if (n % 400 == 0) {
                printf("YES");
            } else {
                printf("NO");
            }
        } else {
            printf("YES");
        }
    } else {
        printf("NO");
    }
    printf("\n");
    return 0;
}
