#include<stdio.h>
int main(){
int buf[100];
  
int a,b,c,d,sum;
fgets(buf, sizeof(buf), stdin);
 sscanf(buf, "%d", &a);
fgets(buf, sizeof(buf), stdin);
 sscanf(buf, "%d", &b);
fgets(buf, sizeof(buf), stdin);
 sscanf(buf, "%d", &c);
fgets(buf, sizeof(buf), stdin);
 sscanf(buf, "%d", &d);
  
sum=(a+b)*(c-d);

printf("%d\nTakahashi", sum);
}