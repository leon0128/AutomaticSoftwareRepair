#include<stdio.h>
int cmp(int*a,int*b){return*a-*b;}
int a[5],b=1;
int main(){
	for(int i=0;i<5;i++)scanf("%d",a+i);
	qsort(a,5,4,cmp);
	for(int i=1;i<5;i++)b+=a[i]!=a[i-1];
	printf("%d\n",b);
}
