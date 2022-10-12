#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>

int main(void){
	int i,j,k,n;
	int count;
	char s[5][10] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
	char s1[10];

	scanf("%s",s1);

	for(i=4;i>=0;i--){
		if(strcmp(s[i],s1)==0){
			printf("%d",5-i);
		}
	}
	return 0;
}
