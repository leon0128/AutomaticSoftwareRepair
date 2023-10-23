#include <stdio.h>
int main (){
	int a=0;
	scanf("%d",&a);
	if(a%4==0)
	{
		if(a%100==0){
			if(a%400==0)
			{
				printf ("YES\n");
			}
			else
			{
				printf ("NO\n");
			}
			}
			else
			{
				printf ("YES\n");
			}
	}
	else
	{
		printf ("NO\n");
	}
	
	return 0;
	}