#include<stdio.h>
#include<stdlib.h>


int main(){
    int N;scanf("%d",&N);
    if(N<=15){
        printf("0%X",N);
    }else if(N>=16){
        printf("%X",N);
    }
    return 0;
}