#include<stdio.h>
 
int main(){
	char s[10];
	scanf("%s",s);

	int n = -1;
	if(s[0] == 'M'){
		n = 5;
	}
	else if(s[0] == 'T' && s[1] == 'u'){
		n = 4;
	}
	else if(s[0] == 'W'){
		n = 3;
	}
	else if(s[0] == 'T' && s[1] == 'h'){
		n = 2;
	}
	else if(s[0] == 'F'){
		n = 1;
	}

	printf("%d\n",n);
	return 0;
}