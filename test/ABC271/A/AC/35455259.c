#include<stdio.h>
int main() {
	int a;
	//char hex[2];
	scanf("%d", &a);
	if(a<10) printf("0%d\n",a);
	else if(a>9 && a<16) printf("0%c\n", a+55);
	else {
		int b = a/16;
		int c = a%16;
		if(b<10) printf("%d", b);
		else printf("%c", b+55);
		if(c<10) printf("%d", c);
		else printf("%c", c+55);
	}
	return 0;
}