#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

 
 
int main(void){
    int x, y, n, m;
    int a = 0, b = 0;
    int count = 0;
    
    scanf("%d %d %d", &x, &y, &n);
    m = n;
    
    while(n >= 3){
        n = n - 3;
        count++;
    }

    count = count*y;

    if(n){
        count += n*x;
    }
    

    printf("%d", count);



    
 
    return 0;
}