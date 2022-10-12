#include <stdio.h>
#include <string.h>
int main(void){
    int n;
    scanf("%d", &n);
    int x = n/16;
    int y = n%16;
    char a[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 'A', 'B', 'C', 'D', 'E', 'F'};
    if(n == 0){
        printf("%s", "00");
    }else{
        if(x == 0){
            printf("%c", '0');
        }else if(x > 0 && 10 > x){
            printf("%d", x);
        }else {
            printf("%c", a[x]);
        }
        if(y == 0){
            printf("%c", '0');
        }else if(y > 0 && 10 > y){
            printf("%d", y);
        }else {
            printf("%c", a[y]);
        }
    }
}