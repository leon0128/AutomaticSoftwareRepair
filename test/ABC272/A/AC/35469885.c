#include<stdio.h>
#include<stdlib.h>

int main(){
 int n;
 int a[100];
 long long s=0;
 scanf("%d",&n);
 for(int i=0;i<n;i++){
     scanf("%d",&a[i]);
     s+=(long long)a[i];
 }printf("%lld",s);
  return 0;
}