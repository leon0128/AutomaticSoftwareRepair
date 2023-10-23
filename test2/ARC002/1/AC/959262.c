#include<stdio.h>
int main(){
int y;
scanf("%d",&y);
printf("%s\n",y%400==0||y%100&&y%4==0?"YES":"NO");
return 0;
}
