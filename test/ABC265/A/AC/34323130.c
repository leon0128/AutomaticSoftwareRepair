#include<stdio.h>

int comb(int X, int Y,int N){
   
    if(N%3==0){
        if(3*X>Y){
            return Y*N/3;
        }
        else{
            return X*N;
        }
    }
    else if(N%3==1){
        if(3*X>Y){
          return Y*(N-1)/3+X;
        }
        else{
            return X*N;
        }
    }
    else{
        if(3*X>Y){
            return Y*(N-2)/3+2*X;
        }
        else{
            return X*N;
        }
    }
}

int main(){
    int X,Y,N;

    scanf("%d %d %d",&X,&Y,&N);

    printf("%d\n",comb(X,Y,N));
    return 0;
}