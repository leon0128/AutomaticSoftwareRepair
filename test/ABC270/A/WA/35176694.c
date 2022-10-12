#include<stdio.h>
int main(void)
{
	int c,a,b;
	scanf("%d%d",&a,&b);
	if(a==7||b==7){
		printf("7\n");
	}
	else if(a==b){
		printf("%d",a);
	}
	else if(a==6&&b==3){
		printf("7\n");
	}
	else if(a==3&&b==6){
		printf("7\n");
	}

	else if(a==6&&b==5){
		printf("7\n");
	}
	else if(a==5&&b==6){
		printf("7\n");
	}
	else if(a==6&&b==4){
		printf("6\n");
	}
	else if(a==4&&b==6){
		printf("6\n");
	}
	else if(a==5&&b==4){
		printf("5\n");
	}
	else if(a==4&&b==5){
		printf("5\n");
	}
	else if(a==4&&b==3){
		printf("7\n");
	}
	else if(a==3&&b==4){
		printf("7\n");
	}
	else if(a==6&&b==2){
		printf("6\n");
	}
	else if(a==2&&b==6){
		printf("6\n");
	}
	else if(a==2&&b==5){
		printf("7\n");
	}
	else if(a==5&&b==2){
		printf("7\n");
	}
	else if(a==4&&b==2){
		printf("6\n");
	}
	else if(a==2&&b==4){
		printf("6\n");
	}
	else if(a==3&&b==2){
		printf("2\n");
	}
	else if(a==2&&b==3){
		printf("2\n");
	}
	else if(a==6&&b==1){
		printf("7\n");
	}
	else if(a==1&&b==6){
		printf("7\n");
	}
	else if(a==5&&b==1){
		printf("5\n");
	}
	else if(a==1&&b==5){
		printf("5\n");
	}
	else if(a==4&&b==1){
		printf("5\n");
	}
	else if(a==1&&b==4){
		printf("5\n");
	}
	else if(a==1&&b==3){
		printf("3\n");
	}
	else if(a==3&&b==1){
		printf("3\n");
	}
	else if(a==2&&b==1){
		printf("3\n");
	}
	else if(a==1&&b==2){
		printf("3\n");
	}
	else if(a==7&&b==0){
		printf("7\n");
	}
	else if(a==0&&b==7){
		printf("7\n");
	}
	else if(a==0&&b==6){
		printf("6\n");
	}
	else if(a==6&&b==0){
		printf("6\n");
	}
	else if(a==0&&b==5){
		printf("5\n");
	}
	else if(a==5&&b==0){
		printf("5\n");
	}
	else if(a==4&&b==0){
		printf("4\n");
	}
	else if(a==0&&b==4){
		printf("4\n");
	}
	else if(a==0&&b==2){
		printf("2\n");
	}
	else if(a==2&&b==0){
		printf("2\n");
	}
	else if(a==0&&b==3){
		printf("2\n");
	}
	else if(a==3&&b==0){
		printf("2\n");
	}
	else if(a==0&&b==1){
		printf("1\n");
	}
	else if(a==1&&b==0){
		printf("1\n");
	}
	return 0;
}