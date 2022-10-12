#include<stdio.h>
int main(void){
 int x,y,n;
 int i,j,z;
 scanf("%d %d %d",&x,&y,&n);
 i=n/3;
 j=n%3;
 z=y*i+x*j;
 printf("%d",z);
 return 0;
}