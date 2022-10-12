#include <stdio.h>   // scanf
#include <string.h>  // strchr

int main(void)
{
	char c[100] = "";
	int a, k = 0;
	int i;
	for(i=0;i<5;i++){
		scanf("%d", &a);
		if (!strchr(c, a+1)) c[k++] = a+1;
	}
	printf("%d\n", k);
}