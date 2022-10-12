#include<stdio.h>
int main(void)
{
	int x,y,n,q,w,e;
	scanf("%d %d %d",&x,&y,&n);
	if(n%3!=0){
		w=n%3;
		e=n/3;
		q=((n/3)*y)+(x*w);
	}
	else{
		q=(n/3)*y;
	}
	if(q>=x*n) printf("%d\n",x*n);
	else printf("%d\n",q);
	return 0;
}