#include<stdio.h>
int main(){
  int a;
  scanf("%d",&a);
  if(a%400==0){
    printf("YES\n");
    return 0;
  }
  if(a%100!=0){
    printf("NO\n");
    return 0;
  }
  if(a%4==0){
    printf("YES\n");
    return 0;
  }
   printf("NO\n");
    return 0;
}