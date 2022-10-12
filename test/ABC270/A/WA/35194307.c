#include<stdio.h>
int main(void)
{
	int a,b,q;
	scanf("%d %d",&a,&b);
	if(a==b) printf("%d\n",a);
	else if(a+b>7){
		printf("7\n");
	}
	else if(a+b<=7){
		if(b!=1&&b!=2&&b!=4){
			if(a==1&&b!=6||a==2&&b!=5||a==4&&b!=3) printf("%d\n",b);
		}
		else if(a!=1&&a!=2&&a!=4){
			if(b==1&&a!=6||b==2&&a!=5||b==4&&a!=3) printf("%d\n",a);
		}
		else printf("%d\n",a+b);
	}
	return 0;
}