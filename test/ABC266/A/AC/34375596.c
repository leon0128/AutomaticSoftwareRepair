#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){

    char *S=(char*)malloc(100*sizeof(char));
    scanf("%s",S);

    int length_of_string=strlen(S);
    int i=(length_of_string)/2;
    printf("%c",S[i]);

}