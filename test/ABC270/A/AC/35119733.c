#include <stdio.h>

int main(void){
  int num1,num2;
  int ans=0;
  scanf("%d%d",&num1, &num2);
  if(num1%2==1||num2%2==1){
    ans+=1;
    num1=(num1/2)*2;
    num2=(num2/2)*2;
  }
  if(num1>=4||num2>=4){
    ans+=4;
    num1=(num1>=4) ? num1-4:num1;
    num2=(num2>=4) ? num2-4:num2;
  }
  if(num1==2||num2==2){
    ans+=2;
  }
  printf("%d\n",ans);
  
  
  
  return 0;
}
  