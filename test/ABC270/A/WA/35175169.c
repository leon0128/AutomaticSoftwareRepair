#include<stdio.h>
int main(void)
{
	int c,a,b;
	scanf("%d%d",&a,&b);
	c=a+b;
	if(c>=7){
		printf("7\n");
	}
	else if(a==b){
		printf("%d\n",a);
	}
	else if(c==6){
		printf("6\n");
	}
	else if(c==5){
		printf("5\n");
	}
	else if(a==0&&b==4){
		printf("2\n");
	}
	else if(a==4&&b==0){
		printf("4\n");
	}
	else if(a==0&&b==1){
		printf("1\n");
	}
	else if(a==1&&b==0){
		printf("1\n");
	}
	else if(a==0&&b==2){
		printf("2\n");
	}
	else if(a==2&&b==0){
		printf("2\n");
	}
	else if(a==1&&b==2){
		printf("3\n");
	}
	else if(a==2&&b==1){
		printf("3\n");
	}
	return 0;
}