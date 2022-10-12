#include<stdio.h>
int X,Y,N;
int main(){
	scanf("%d%d%d",&X,&Y,&N);
	printf("%.f\n",fmin(X*N,N/3*Y+N%3*X));
}
