#include <stdio.h>

int main() {
    char a[11][11];
    int min1 = 11, max1 = 0;
    int min2 = 11, max2 = 0;

    for (int i = 0; i < 10; ++i) {
         for (int j = 0; j < 10; ++j) {
            scanf("%c", &a[i][j]);
          }
    }

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if(a[i][j] == '#') {
                if(i < min1) min1 = i;
                if(i > max1) max1 = i;
                if(j < min2) min2 = j;
                if(j > max2) max2 = j;
            }
        }
    }

    printf("%d %d\n%d %d", min1 + 1, max1 + 1, min2 , max2 );

    return 0;
}