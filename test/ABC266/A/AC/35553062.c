#include<stdio.h>
#include<string.h>
char S[111];
int main(){
	gets(S);printf("%c\n",S[strlen(S)/2]);
}
