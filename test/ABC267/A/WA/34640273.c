#include<stdio.h>
int main(void){
int N;
int M;
scanf("%d %d",&N,&M);
int A[N];
for(int i = 0;i<N;i++)
	scanf("%d",&A[i]);
int goukei=0;
int z=0;
int max=-5000000;
for(;;){
	for(int i = z;i<z+M;i++){
		goukei= goukei + A[i]*(i-z+1);
	}
	z++;		
	if(goukei > max)
	max = goukei;
	if(z+M>N)
		break;
		goukei =0;
}
	printf("%d",max);
return 0;
}
