#include <stdio.h>

int main ( void ){
	int x,y,n;
	scanf("%d %d %d",&x,&y,&n);
	int price,price_;
	price = (n/3)*y + (n%3)*x;
	price_ = x*n;
	
	if(price <= price_){
		printf("%d\n",price);
	} else {
		printf("%d\n",price_);
	}
	return 0;
}