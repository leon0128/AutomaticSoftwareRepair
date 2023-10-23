#include <stdio.h>

#define toBool(x)	(x == 0 ? 0 : 1)
int main(){
	unsigned int Y;
	char res[] = "NO";

	scanf("%d", &Y);
	
	Y = (!(toBool(Y % 4)) & toBool(Y % 100)) | !(toBool(Y % 400));
	
	printf("%s\n", (Y == 0) ? "NO" : "YES");
	return 0;
}
