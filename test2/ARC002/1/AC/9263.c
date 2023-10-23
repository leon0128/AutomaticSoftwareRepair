#include <stdio.h>

int main(){
	int y;
	scanf("%d",&y);
	if(!(y%400))puts("YES");
	else if(!(y%100))puts("NO");
	else if(!(y%4))puts("YES");
	else puts("NO");
	return 0;
}
