#include<stdio.h>
int main(void)
{
	int N[5];
	int M[5]={1,1,1,1,1};
	for(int i=0; i<5; i++)
		scanf("%d",&N[i]);

	for(int i=0; i<4; i++) {
		for(int j=i+1;j<5;j++)
			if(N[i]==N[j]) M[j]=0;
	}

	int ans=0;
	for(int i=0;i<5;i++)
		ans+=M[i];
	printf("%d\n",ans);
	return 0;
}