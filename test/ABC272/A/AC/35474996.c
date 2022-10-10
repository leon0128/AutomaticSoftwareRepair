#include<stdio.h>
int main(void)
{
  int n,i,sum=0,a;
  scanf("%d",&n);
  for(i=0;i<n;i++){
    scanf("%d",&a);
    sum+=a;
  }
  printf("%d",sum);
  return 0;
}