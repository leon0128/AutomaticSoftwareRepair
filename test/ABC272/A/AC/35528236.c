#include<stdio.h>

void main(){
    int n;
    int i,A[100],sum=0;
    scanf("%d\n",&n);
    for(i=0;i<n;i++){
        scanf("%d",&A[i]);
    }
    for(i=0;i<n;i++){
        sum+=A[i];
    }
    printf("%d",sum);
}