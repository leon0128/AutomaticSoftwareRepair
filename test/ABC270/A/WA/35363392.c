#include <stdio.h>
int main()
{
	int A,B;
	scanf("%d %d", &A, &B);
	if((A+B)<7){
	  printf("%d\n",(A+B));
	}
else if(A==B){
printf("%d\n",A);
}
else if((A+B)==7){
printf("%d\n",7);
}
	else{
	  printf("%d\n",7);
	}
	return 0;
}