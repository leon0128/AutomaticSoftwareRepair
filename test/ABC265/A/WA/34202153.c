#include <stdio.h>
int main(){
    int X,Y,N;
    scanf("%d %d %d",&X,&Y,&N);
    int c = 0;
    if(X*3<=Y){
        c += (N/3)*Y;
        c += (N%3)*X;
    }else{
        c += X*N;
    }
    printf("%d\n",c);
    return 0;
}