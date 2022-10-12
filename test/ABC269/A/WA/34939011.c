#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
 
 
int main(void){
 
int a,b,c,d,i,j,x=0;;
char S[10][10];

for(i=0;i<10;i++){
scanf("%c %c %c %c %c %c %c %c %c %c",&S[i][0],&S[i][1],&S[i][2],&S[i][3],&S[i][4],&S[i][5],&S[i][6],&S[i][7],&S[i][8],&S[i][9]);
}
 
for(i=0;i<10;i++){
	for(j=0;j<10;j++){
		if(S[i][j]=='#'){
			a=i+1;
          if(i==0){
			c=j+1;
          }
          else{
            c=j;
          }
			x=1;
         
			break;
		}
	}
	if(x==1){
		break;
	}
}
x=0;
for(i=9;i>=0;i--){
	for(j=9;j>=0;j--){
		if(S[i][j]=='#'){
			b=i+1;
          if(i==9){
			d=j+1;
          }
          else{
            d=j;
          }
			x=1;
			break;
		}
	}
	if(x==1){
		break;
	}
}
  
 
printf("%d %d\n%d %d",a,b,c,d);


	return(0);
}