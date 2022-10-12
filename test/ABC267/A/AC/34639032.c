#include <stdio.h>

int main (void)
{
  	int a;
	char s[10]={'\0'};
  	scanf("%s",s);
  	if(s[1]=='o'){
    	a = 5;
    }else if(s[1]=='u'){
    	a = 4;
    }else if(s[1]=='e'){
    	a = 3;
    }else if(s[1]=='h'){
    	a = 2;
    }else if(s[1]=='r'){
    	a = 1;
    }
  
  	printf("%d",a);
}