#include<stdio.h>
int main(void)
{
  int a,b,i,c=0;
  int s[3]={1,2,4};
  scanf("%d %d",&a,&b);
  for(i=0;i<3;i++){
    if(a%2==1 || b%2==1){
      c+=s[i];
    }
    a/=2;
    b/=2;
  }
  printf("%d",c);
  return 0;
}