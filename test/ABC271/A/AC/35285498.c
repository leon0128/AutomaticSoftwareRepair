#include<stdio.h>

int main(){
  int n;
  scanf("%d",&n);
  char num[7]={"ABCDEF"};
  int digit[2];
  if(n<=15){
    printf("%d",0);
    if(n<=9){
      printf("%d",n);
    }else {
      printf("%c",num[n%10]);
    }
  }else {
      digit[0]=n/16;
      digit[1]=n%16;
      for(int i=0;i<2;i++){
        if(10<=digit[i]){
          printf("%c",num[digit[i]%10]);
        }else{
          printf("%d",digit[i]);
        }
      }
  }
  putchar('\n');
  return 0;
}