#include<stdio.h>

int main(void){
char str[32];
int n;
fgets(str,sizeof(str),stdin);
sscanf(str,"%d",&n);
if(n%400==0)
puts("YES");
else if(n%100==0)
puts("NO");
else if(n%4==0)
puts("YES");
else puts("NO");return 0;
}