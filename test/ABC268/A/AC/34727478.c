#include<stdio.h>
int main(){
 int a[5];
 int b[101]={};
  for(int i=0;i<5;i++){
    scanf("%d",&a[i]);
  	b[a[i]]=1;
  }
  int cnt=0;
  for(int i=0;i<=100;i++){
    if(b[i]==1)cnt++;
  }printf("%d",cnt);
  return 0;
}