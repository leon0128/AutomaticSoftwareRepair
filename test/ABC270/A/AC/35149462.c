#include <stdio.h>

struct packed_struct {
	unsigned char : 2;
  	unsigned char taka : 3;
  	unsigned char aoki : 3;
  	unsigned char sune : 3;
};


int main(void) {
  	int input_current;
  	struct packed_struct data;
  	input_current = (int) (getchar() - '0');
  	data.taka = input_current;
  	getchar();
  	input_current = (int) (getchar() - '0');
  	data.aoki = input_current;
  	data.sune = data.taka | data.aoki;
	printf("%d", data.sune);
  
  
	return 0;
}
