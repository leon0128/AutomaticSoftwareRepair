#include <stdio.h>

int main()

{

	char x[10];	int a=1,b=2,c=3,d=4,e=5;

	

	scanf("%s", x);

	

	if(x[0]=='M') printf("%d",e);

	if(x[1]=='u') printf("%d",d);

	if(x[0]=='W') printf("%d",c);

	if(x[1]=='h') printf("%d",b);

	if(x[0]=='F') printf("%d",a);

	

	return 0;

}