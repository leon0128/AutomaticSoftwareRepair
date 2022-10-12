#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() 
{
	int i=0;
	char in[11];
	int col[8]={};
	scanf("%s",&in);
//	for(i=1;i<8;i++)
//		printf("%c\n",in[i]);
	if(in[0]==1)
		printf("Yes\n");
	else
		printf("No\n");
	if(in[0]==1)
		return 0;
	if(in[6]=='1')
		col[1]=1;
	if(in[3]=='1')
		col[2]=1;
	if(in[7]=='1'||in[1]=='1')
		col[3]=1;
	if(in[4]=='1'||in[0]=='1')
		col[4]=1;
	if(in[8]=='1'||in[2]=='1')
		col[5]=1;
	if(in[5]=='1')
		col[6]=1;
	if(in[9]=='1')
		col[7]=1;
//	for(i=1;i<8;i++)
//		printf("%d\n",col[i]);
	for(i=1;i<6;i++)
		if(col[i]==1)
			if(col[i+1]==0)
				if(col[i+2]==1)
					printf("Yes");
				else
					printf("No");
}