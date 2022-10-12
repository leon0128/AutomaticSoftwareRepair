#include <stdio.h>

int main ()
{
	int a, b, max, min;
	scanf ("%d %d", &a, &b);
	
	if (a-b>0)
	{
		max = a;
		min = b;
	}
	if (a-b<0)
	{
		max = b;
		min = a;
	} 
	
	if (a==b)
	{
		printf ("%d", a);
	}
	else if(min==0)
	printf ("%d", max);
	else
	{
		if (max==1)
		printf ("1");
		if (max==2)
		printf ("3");
		if (max==3)
		printf("3");
		if (max==4)
		printf ("%d", min+4);
		if (max==5)
		{
			if (min==1 || min==4)
			printf ("5");
			if (min==2 || min==3)
			printf ("7");
		}
		if (max==6)
		{
			if (min==2 || min==4)
			printf ("6");
			if (min==1 || min==3 || min==5)
			printf ("7");
		}
	}
	
	return 0;
}