#include<stdio.h>

int main(){
int N;
int A[101],sum =0;
scanf("%d",&N);
for(int i= 0;i < N;i++){
scanf("%d",&A[i]);
sum += A[i];
}
printf("%d",sum);
    return 0;
}