#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

int main(void){

int a[200],sum=0,N;
scanf("%d",&N);
for(int i=0;i<N;i++){
scanf("%d",&a[i]);
sum += a[i];
}

printf("%d",sum);
return 0;
    
}