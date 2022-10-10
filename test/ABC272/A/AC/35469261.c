//ABC272_A
#include <stdio.h>
int main(void){
	int a,n,sum=0;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&a);
		sum+=a;
	}
	printf("%d\n",sum);
	return 0;
}