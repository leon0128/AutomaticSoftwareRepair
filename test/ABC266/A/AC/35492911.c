#include<stdio.h>
#include<string.h>
int main(){
    char S[100];
    gets(S);
    int n = strlen(S);
    printf("%c", S[(n+1)/2-1]);
}