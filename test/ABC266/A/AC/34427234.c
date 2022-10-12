#include <stdio.h>
int main(void){
char S[500];
int i;
int count = 0;

scanf("%s" , S);

for(i = 0; S[i] != '\0'; i++){
count += 1;
}

count /= 2;

printf("%c" , S[count]);
}