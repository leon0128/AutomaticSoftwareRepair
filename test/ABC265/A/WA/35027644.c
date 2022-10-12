#include<stdio.h>
int main(){
	int x,y,n,xn,yn,xw,yw;
  	
  	scanf("%d%d%d",&x,&y,&n);
  	xn=n%3;
  	yn=n-xn;
  	xw=x*n;
  	yw=x*xn+y*yn;
  	if(xw < yw){
  		printf("%d",xw);
    }else{
    	printf("%d",yw);
    }
  return 0;
}