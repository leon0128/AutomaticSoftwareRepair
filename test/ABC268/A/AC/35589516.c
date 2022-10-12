#include <stdio.h>

int main()
{
	int A , B , C , D , E ;
	scanf("%d%d%d%d%d",&A,&B,&C,&D,&E) ;
	
	int a[]={A,B,C,D,E,};
	for(int i=0;i<=3;i++){
		for(int j=i;j<4;j++){
			if(a[i]==a[j+1]){
				a[j+1]=-1 ;
			}
		}
	}
	int bet=0 ;
	for(int i=0;i<=4;i++){
		if(a[i]!=-1){
			bet++ ;
		}
	}
	printf("%d",bet);
	return 0;
}