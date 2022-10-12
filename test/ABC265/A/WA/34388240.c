#include<stdio.h>
int main(void)
{
int X;
int Y;
int N;
int k;//個数
int z;//あまり
	k = 0;
	z = 0;
int goukei;
scanf("%d %d %d",&X,&Y,&N);
if(3*X>Y){
k = N/3;
z = N % 3;
	printf("A");
goukei = k*Y + z*X;
}else{
goukei = N*X;
}

	printf("%d",goukei);




return 0;
}