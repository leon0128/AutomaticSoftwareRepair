#include <stdio.h>

int main(void){

    int X,Y,N,a1,b1,ans1,ans2;
    scanf("%d %d %d",&X,&Y,&N);
    a1 = N%3;
    b1 = N/3;
    ans1 = X*a1 + Y*b1;
    ans2 = N*X;

    if(ans1<ans2){
        printf("%d\n",ans1);
    }else{
        printf("%d\n",ans2);
    }

    return 0;

}