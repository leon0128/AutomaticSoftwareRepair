#include<stdio.h>
int main(){
char s[1000];
int len=0,i,x;
scanf("%s",s);
for(i=0;s[i]!='\0';i++){
        len++;
}
x=(len/2);
printf("%c",s[x]);
return 0;
}