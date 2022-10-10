#include<stdio.h>

int main (){
int a,i,sum,N[110];
  for(i=0;i<110;i++){
  N[i]=0;}
  sum=0;
  scanf("%d",&a);
  for(i=0;i<a;i++){
  scanf("%d",&N[i]);
  sum+=N[i];}

  printf("%d\n",sum);
  
}