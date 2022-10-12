#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

int main(void){
  
int N,X,Y;
scanf("%d%d%d",&X,&Y,&N);
int ans;
if(X*3>=Y){
    printf("%d",(N/3)*Y+(N%3)*X);
    return 0;
}
else
printf("%d",X*N);
return 0;    
}