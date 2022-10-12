#include<stdio.h>
int main() {
	long int decimalNumber,remainder,quotient;
	int i=1,j,temp;
	char hexadecimalNumber[256];
	//printf("Enter any decimal number: ");
	scanf("%ld",&decimalNumber);
	quotient = decimalNumber;
	if(decimalNumber<=9)
	{
		printf("%d",0);
		printf("%d",decimalNumber);
		
	}
	else{
		while(quotient!=0) {
		temp = quotient % 16;
		
		if( temp < 10)
		           temp =temp + 48; else
		         temp = temp + 55;
		hexadecimalNumber[i++]= temp;
		quotient = quotient / 16;
	}
	//printf("%d",decimalNumber);
	//printf("%d",i);
	
	if(i<=2)
	{
		printf("%d",0);
	}
	for (j = i-1  ;j>0;j--)
	      printf("%c",hexadecimalNumber[j]);
	}
	return 0;
}