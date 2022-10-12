#include<stdio.h>
int main()
{
	int A,B,t;
	scanf("%d %d",&A,&B);
	if(A>B)
	{
		t=A;
		A=B;
		B=t;
	}
	if(A==0)
	printf("%d",B);
	else if(A==B)
	printf("%d",A);
	else if((B==7)||(A==5&&B==6)||(A==3&&(B==4||B==5||B==6))||(A==2&&B==5)||(A==1&&B==6))
	printf("7");
	else if(B==6||(A==2&&B==4))
	printf("6");
	else if(B==5||(A==1&&B==4))
	printf("5");
	else
	printf("3");
	
	return 0;
}
