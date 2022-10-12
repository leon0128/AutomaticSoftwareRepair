#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

int main(void){


int A[10],B[1010],count=0;
for(int i=0;i<5;i++){
scanf("%d",&A[i]);
B[A[i]]=1;
}

for(int i=0;i<101;i++)
{
    if(B[i]==1){
        count++;
    }
}
printf("%d",count);
return 0;    
}