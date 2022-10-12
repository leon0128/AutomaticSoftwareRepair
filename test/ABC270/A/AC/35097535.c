#include <stdio.h>

int main(void) {
	// your code goes here
	int a,b;
	int an1=0,an2=0,an3=0;
	scanf("%d %d",&a,&b);
	if(a==1||a==3||a==5||a==7){
	    an1=1;
	}
	if(b==1||b==3||b==5||b==7){
	    an1=1;
	}
	if(a==2||a==3||a==6||a==7){
	    an2=1;
	}
	if(b==2||b==3||b==6||b==7){
	    an2=1;
	}
	if(a==4||a==5||a==6||a==7){
	    an3=1;
	}
	if(b==4||b==5||b==6||b==7){
	    an3=1;
	}
	printf("%d",an1+2*an2+4*an3);
	
	
	return 0;
}