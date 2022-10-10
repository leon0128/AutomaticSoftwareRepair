#include <stdio.h>

int main(void){
    int n = 0;
    scanf("%d", &n);
    int a[100] = {0};
    for(int i = 0; i < n; i++){
        int num = 0;
        scanf("%d", &num);
        a[i] = num;
    }
    int sum = 0;
    for(int i = 0; i < n; i++){
        sum += a[i];
    }
    printf("%d", sum);
}