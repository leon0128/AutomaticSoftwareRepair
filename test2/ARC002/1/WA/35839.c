#include <stdio.h>

int main(){
	int input;
	int uruu = 0;

	scanf("%d",&input);
	if((input % 4) == 0) uruu = 1;
	if((input % 100) == 0) uruu = 0;
	if((input % 400) == 0) uruu = 1;

	if(uruu == 0) printf("No\n");
	if(uruu == 1) printf("Yes\n");

	return 0;
}