#include <stdio.h>

int main ()
{
	int a, b, max, min;
	scanf ("%d", &a);
	scanf ("%d", &b);
	
	if (a==b)
	{
		printf ("%d", a);
	 } 
	 
	if (a-b>0)
	{
		max = a;
		min = b;
	} else if (b-a>0)
	{
		max = b;
		min = a;
	}
	 
	 
	if (max==2 && min!=0)
	printf ("3");
	if (max==3)
	printf ("3");
	if (max==4 && min!=0)
	{
		switch (min)
		{
			case 1:
				printf ("5");
				break;
			case 2:
				printf ("6");
				break;
			case 3:
				printf ("7");
				break;
		}
	}
	if (max==5 && min!=0)
	{
		if (min==1 || min==4)
		printf ("5");
		else 
		printf ("7");
	}
	if (max==6 && min!=0)
	{
		if (min==1 || min==3 || min==5)
		printf ("7");
		else 
		printf ("6");
	}
	
	if (min==0)
	printf ("%d", max);
	
	return 0;
}