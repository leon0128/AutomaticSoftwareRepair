#include <stdio.h>
int main(){
    int x, y, n, apple=0, num1=0, num2=0, sum=0;
    scanf("%d %d %d", &x, &y, &n);

    while(apple<=n){
        apple = apple + 3;
        num1++;
    }
    num1--;
    apple = apple-3;

    while(apple!=n){
        apple++;
        num2++;
    }

    sum = (num1*y) + (num2*x);

    printf("%d", sum);
    return 0;
}
