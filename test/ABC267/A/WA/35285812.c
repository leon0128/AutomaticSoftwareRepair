#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() 
{
	int i=0,j=0;
	char in[11];
	int col[8]={};
	scanf("%s",&in);

	if(in[0]=='1')
	{	printf("No");
		return 0;
	}
	if(in[6]=='1')
		col[1]=1;
	if(in[3]=='1')
		col[2]=1;
	if(in[7]=='1'||in[1]=='1')
		col[3]=1;
	if(in[4]=='1')
		col[4]=1;
	if(in[8]=='1'||in[2]=='1')
		col[5]=1;
	if(in[5]=='1')
		col[6]=1;
	if(in[9]=='1')
		col[7]=1;

	for(i=2;i<7;i++)
	{
		if(col[i]==0 && col[i-1]==1)
			for(j=i;j<8;j++)
				if(col[j]==1)
				{
					printf("Yes");
					return 0;
				}
	}
	printf("No");
}