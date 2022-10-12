#include "stdio.h"

int main(){
    int ap_1;
    int ap_3;
    int num;
    int num_1;
    int num_3;
    int money;
    
	(void)scanf("%d",&ap_1);
	(void)scanf("%d",&ap_3);
	(void)scanf("%d",&num);
	if(((ap_1 * 3) > ap_3)&&(num < 3)){
	    num_3 = num / 3;
	    num_1 = num % 3;
	}else {
		num_1 = num;
		num_3 = 0;
	}
	money = ap_1 * num_1 + ap_3 * num_3;
    printf("%d\n",money);
    return 0;
}