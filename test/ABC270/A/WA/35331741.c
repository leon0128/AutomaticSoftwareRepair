#include<stdio.h>

int main()
{
	int A,B,c;
	scanf("%d%d",&A,&B);
	if(A==0)
	{
		c=B;
		printf("%d",c);
	}else if(B==0)
	{
		c=A;printf("%d",c);	
	}else if(A==7||B==7||((A==6)&&(B==1||B==3||B==5))||((A==5)&&(B==3||B==6))||((A==4)&&(B==3))||((A==3)&&(B==4||B==5||B==6))||((A==2)&&(B==5))||((A==1)&&(B==6)))
	{	
		c=7;
		printf("%d",c);
	}else if(((A==2||A==4||A==6)&&(B==6))||((A==6)&&(B==2||B==4)))
	{
		c=6;
		printf("%d",c);
	}else if(((A==1||A==4||A==5)&&(B==5))||((A==5)&&(B==1||B==4)))
	{
		c=5;
		printf("%d",c);	
	}else if(A==4||B==4)
	{
		c=4;
		printf("%d",c);	
	}else if(((A==1||A==2||A==3)&&(B==3))||((A==3)&&(B==1||B==2)))
	{
		c=3;
		printf("%d",c);	
	}else if(A==2&&B==2)
	{
		c=2;
		printf("%d",c);	
	}else if(A==1&&B==1)
	{
		c=1;
		printf("%d",c);
	}
		
	
	return 0;	

}
	
	