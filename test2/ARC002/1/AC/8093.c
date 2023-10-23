#include<stdio.h>
#include<string.h>

int main(void){
  int flag,i;
  char ans[4]="NO",YES[4]="YES";
  flag = 0;
  scanf("%d",&i);
  flag = (i%4)? 0:
    (i%100)? 1:
       (i%400)? 0:
     1;
  if(flag){
    strcpy(ans,YES);
  }
  printf("%s\n",ans);
  return 0;
}
