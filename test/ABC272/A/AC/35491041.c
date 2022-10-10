#include<stdio.h>
#include<stdlib.h>


int main(){
    int N;scanf("%d",&N);
    int i,sum=0,*a=(int*)malloc(sizeof(int)*N);
    for(i=0;i<N;i++){
        scanf("%d",a+i);
        sum+=a[i];
    }
    printf("%d",sum);
    return 0;
}