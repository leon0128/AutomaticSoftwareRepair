#include <stdio.h>

int main(void){
    int X,Y,N;
    
    do{
    scanf("%d",&X);
    scanf("%d",&Y);
    }while(X<1||X>Y||Y>100);
    do{
    scanf("%d",&N);
    }while(N<1||N>100);
    
    if(N>3){
        if(X*3<Y){
            printf("%d",X*N);
        }
        else{
            printf("%d",(N/3)*Y+(N%3)*X);
        }
    }
    else printf("%d",X*N);
    return 0;
}