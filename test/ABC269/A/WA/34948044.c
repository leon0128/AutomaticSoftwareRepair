#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
 
 
int main(void){
 
int a,b,c,d,i,j,x=0;

scanf("%d",&x);
j=0;
for(i=0;x>0;i++){
	if(x%2==1){
      if(i==0){
        j=0;
      }
      else{
		j=pow(2,i);
      }
      for(a=i;a>=0;a--){
		printf("%d\n",j);
        j=j+1;
      }
	}
  x=x/2;
}
		




	return(0);
}