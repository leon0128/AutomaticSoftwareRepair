#include <stdio.h>

int main()
{
    int y;

    scanf("%d", &y);

    if (y % 100 == 0) {
        if (y % 400 == 0) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }   
    } else if (y % 4 == 0) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }   

    return 0;
}
