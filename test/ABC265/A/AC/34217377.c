#include<stdio.h>

int main(){
    int x, y, n;
    scanf("%d %d %d", &x, &y, &n);
    int a, b, c, m;
    a = x*n;

    m = n/3;
    n = n-m*3;
    b = y*m+x*n;

    if(a <= b){
        printf("%d\n", a);
    }else{
        printf("%d\n", b);
    }
    
    return 0;


}