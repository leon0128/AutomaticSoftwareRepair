#include<stdio.h>
int main(){
	char a;
	a=getchar();
	switch(a){
		case('M'):{
			printf("1");
			break;
		}
		case('T'):{
			char b;
			b=getchar();
			if(b=='h')
			printf("4");
			else printf("2");
			break;
		}
		case('W'):{
			printf("3");
			break;
		}
		case('F'):{
			printf("5");
			break;
		}
	}
		
	
	return 0;
} 