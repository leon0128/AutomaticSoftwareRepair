#include<stdio.h>

int main(){
	int i=0,n;
	scanf("%d", &n);
	int a[n];
	for(i=0;i<n;i++) scanf("%d", &a[i]);
	int s=0;
	for(i=0;i<n;i++) s+=a[i];
	printf("%d",s);
	return 0;
}