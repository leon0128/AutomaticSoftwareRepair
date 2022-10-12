#include <stdio.h>

int main()
{
	int A , B , C , D , E ;
	int a[5] = { A , B , C , D , E} ;
	
	for(int i = 0; i < 5 ; i ++){
		scanf("%d", & a[i]) ;
	}
	int bet = 5 ;
	
	for(int i =0 ; i < 3 ; i ++){
		for(int j = i ; j<4&&i==0 ; j ++){
			if(a[i] == a[j+1] ){
				bet -- ;
			}
		}
		if(a[i]!=a[i+1]){
			for(int n=i;n<4;n++){
				if(a[i]=a[n+1]){
					bet --;
				}
			}
		}
		else{break;}
		
	}
	printf("%d",  bet) ;
	return 0 ;
	
}