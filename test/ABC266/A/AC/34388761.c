#include<stdio.h>
#include<string.h>

int main(void)
{
   char S[100];
   int len;
   scanf("%s", S);
   len = strlen(S);
   printf("%c", S[(len - 1) / 2]);
}