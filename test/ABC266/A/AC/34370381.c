#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>
int main(void){
char S[110];
int N;

scanf("%s",S);

N=strlen(S);

printf("%c",S[N/2]);

 return 0;
}