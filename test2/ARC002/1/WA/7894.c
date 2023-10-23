#include <stdio.h>

int main()
{
	int Y;
	scanf("%d",&Y);

	if(Y%4 == 0){
		if(Y%100==0){
			printf("NO");
			return 0;
		}
		printf("YES");
		return 0;
	}
	if(Y%400 == 0)
		printf("YES");
	else printf("NO");
	return 0;
}
