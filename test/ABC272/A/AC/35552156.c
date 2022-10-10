#include<stdio.h>
int N,s;
int main(){
	scanf("%d",&N);
	for(;N--;){
		int a;
		scanf("%d",&a);
		s+=a;
	}
	printf("%d\n",s);
}
