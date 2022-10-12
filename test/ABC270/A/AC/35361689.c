#include<stdio.h>

int main()
{
	int A,B;
	int ji1=0,ji2=0;
	int p,q;
	scanf("%d%d",&A,&B);

	if(A%2!=0){
		ji1=1;
		A-=1;
		p=A/2;
	}
	else{
		p=A/2;
	}

	if(B%2!=0){
		ji2=1;
		B-=1;
		q=B/2;
	}
	else{
		q=B/2;
	}
	int sum=0;
	if(ji1==1||ji2==1){
		sum+=1;
		if((p==1||q==1)&&(p!=3&&q!=3)){
			sum+=2;
		}
		if((p==2||q==2)&&(p!=3&&q!=3)){
			sum+=4;
		}
		if((p==3||q==3)){
			sum+=6;
		}
	}
	else{
		if((p==1||q==1)&&(p!=3&&q!=3)){
			sum+=2;
		}
		 if((p==2||q==2)&&(p!=3&&q!=3)){
			sum+=4;
		}
		if(p==3||q==3){
			sum+=6;
		}
	}
	printf("%d",sum);
	return 0;
}