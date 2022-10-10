#include<stdio.h>
int main(){
  int n,s=0,a;
  scanf("%d",&n);
  while(n--){
    scanf("%d",&a);
    s+=a;
  }
  printf("%d\n",s);
  return 0;
}
