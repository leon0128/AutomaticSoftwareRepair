#include<stdio.h>

void main(){
    int A[5],i,j,num=5;
    for(i=0;i<5;i++){
        scanf("%3d",&A[i]);
    }
    for(i=0;i<5;i++){
        for(j=i+1;j<5;j++){
            if(A[i]==A[j]){
                num=num-1;
                break;
            }
        }
    }
    printf("%1d",num);
}