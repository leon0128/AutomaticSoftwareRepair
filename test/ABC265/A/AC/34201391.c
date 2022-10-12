#include<stdio.h>
int main(void) {
	int n, x, y, i, t;
	scanf("%d %d %d", &x, &y, &n);
    i = x * n;
    t = y * (n / 3) + x * (n % 3);
    if (i < t){
        printf("%d", i);
    }
    else{
        printf("%d", t);
    }
    return 0;
}