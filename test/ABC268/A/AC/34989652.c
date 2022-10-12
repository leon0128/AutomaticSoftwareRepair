#include <stdio.h>
#include <string.h>

int main ()
{
	int i,j,count=0,a,b,c,d,e;
  	scanf("%d%d%d%d%d",&a,&b,&c,&d,&e);
  	count++;
  	if(a!=b){
      	count++;
    }
  	if(a!=c && b!=c){
    	count++;
    }
  	if(a!=d && b!=d && c!=d){
    	count++;
    }
  	if(a!=e && b!=e && c!=e && d!=e){
    	count++;
    }
  	printf("%d",count);
}