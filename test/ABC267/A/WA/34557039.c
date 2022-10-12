#include <stdio.h>

int main(void)
{
	int n,m;
	int a[21000];
	int i,j;
	long int sum,max=0;
	
	scanf("%d %d",&n,&m);
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	
	for(i=0;i<=n-m;i++){
		sum = 0;
		for(j=0;j<m;j++){
			sum += (j+1)*a[i+j];
		}
		//printf("%d\n",sum);
		if(sum > max){
			max = sum;
		}
	}
	printf("%d\n",max);
	
	return 0;
}