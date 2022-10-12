#include <stdio.h>
#include <stdlib.h>

int Imin(int a, int b){
    if(a<b) return a;
    else return b;
}

int main(void){
    int X,Y,N;
    scanf("%d%d%d",&X,&Y,&N);

    printf("%d\n", Imin(N*X, Y*(N/3)+X*(N%3)));

    return 0;
}