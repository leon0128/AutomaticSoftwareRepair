#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(void){
    int X,Y,N; int sum=0;
    scanf("%d %d %d",&X,&Y,&N);
    int x = X*3;
    if(Y>x){
        sum = X*N;
    }else{
        while(N<3){sum += Y; N -= 3;}
        sum += X*N;
    }
    printf("%d\n",sum);
    return 0;
}