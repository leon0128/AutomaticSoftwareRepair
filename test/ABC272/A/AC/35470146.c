#include<stdio.h>

int main(void)
{
	int n,i,ans,temp;
	ans=0;
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%d",&temp);
		ans+=temp;
	}
	printf("%d\n",ans);
	return 0;
}