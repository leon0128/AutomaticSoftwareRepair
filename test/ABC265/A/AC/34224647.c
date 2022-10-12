#include<stdio.h>
int main(void){
 int x,y,n;
 int i,j,z1,z2;
 scanf("%d%d%d",&x,&y,&n);
 i=n/3;
 j=n%3;
 z1=y*i+x*j;
 z2=x*n;
 if(z1<z2){
  printf("%d",z1);
 }
 else
   printf("%d",z2);
 return 0;
}