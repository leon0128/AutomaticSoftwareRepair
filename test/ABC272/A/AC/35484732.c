#include<stdio.h>

int main(void){
  int n,i,result;
  int num;
  result = 0;

  scanf("%d",&n);
  for(i=0;i<n;i++){
    scanf("%d",&num);
    result += num;
  }

  printf("%d",result);

}
