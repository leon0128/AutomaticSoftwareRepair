#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

int main(void){

char s[120];
scanf("%s",s);
int ans=strlen(s);
ans/=2;
printf("%c",s[ans]);
return 0;
    
}