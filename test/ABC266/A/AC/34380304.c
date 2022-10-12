#include <stdio.h>
#include <string.h>


int main(void)
{
int i,j;
char s[100];
int n;
int t = 0;
  
scanf("%s",s);
n = strlen(s);
  
//printf("%s",s);
//printf("%d",n);
//printf("%c",s[0]);  
printf("%c",s[(n)/2]);




return(0);
}