#include<stdio.h>
char S[11],T[11][11]={ "Monday", "Tuesday", "Wednesday", "Thursday", "Friday" };
int main(){
	scanf("%s",S);
	int i=0;
	for(;strcmp(S,T[i]);i++);
	printf("%d\n",5-i);
}
