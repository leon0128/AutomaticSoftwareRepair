#include<stdio.h>

int main()
{
	int year;
	int flag=0;

	scanf("%d",&year);

	if( year%4 == 0 ){ flag = flag | 1;}
	if( year%100==0 ){ flag = flag | 2;}
	if( year%400==0 ){ flag = flag | 4;}

	if(flag&4){ puts("YES");}
	else if(flag&2){ puts("NO");}
	else if(flag&1){ puts("YES");}
	else { puts("NO");}

	return 0;
}