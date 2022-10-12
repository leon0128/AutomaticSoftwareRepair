#include <stdio.h>
int main(void){
    int X,Y,N;
    scanf("%d %d %d",&X,&Y,&N);
    if(N<3){
        printf("%d",X*N);
    }
    else if(Y>X*3){
        printf("%d",X*N);
    }
    else{
        int a=N%3;
        int b=N/3;
        printf("%d",a*X+b*Y);
    }
    return 0;
}