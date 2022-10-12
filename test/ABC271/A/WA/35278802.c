#include <stdio.h>
#include <string.h>
int main(void){
    int n;
    char a[17] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 'A', 'B', 'C', 'D', 'E', 'F'};
    scanf("%d", &n);
    int x = n%16;
    int y = n/16;
    printf("%c%c", a[y], a[x]);
}