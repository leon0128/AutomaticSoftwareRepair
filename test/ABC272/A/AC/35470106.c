#include<stdio.h>
int main(void){
  int n,a;
  int cou=0;
  scanf("%d",&n);
  for(int i=0;i<n;i++){
   scanf("%d",&a);
    cou+=a;
  }
  printf("%d",cou);
 return 0; 
}