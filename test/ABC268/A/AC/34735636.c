//ABC268_A
#include <stdio.h>
#include <stdlib.h>
int cmp(const void *p, const void *q){
	return *(int*)p - *(int*)q;
}

int main(void){
	int a[4]={},cnt=1;
	for(int i=0;i<5;i++) scanf("%d",&a[i]);
	qsort(a,5,sizeof(int),cmp);
	
//	for(int i=0;i<5;i++) printf("%d ",a[i]);

	for(int i=0;i<4;i++) if(a[i]!=a[i+1]) cnt++;
	printf("%d\n",cnt);
	return 0;
}