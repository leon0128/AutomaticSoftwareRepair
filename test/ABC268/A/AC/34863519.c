#include<stdio.h>
int main(){
  int n[5],a=5,nn[5];
  for(int i=0;i<5;i++){
    scanf("%d",&n[i]);
    
  }
  for(int i=0;i<5;i++){
      nn[i]=n[i];
  }
  for(int i=0;i<5;i++){
      for(int j=i+1;j<5;j++){
          if(n[i]==n[j]){
              a--;
              break;
          }
      }
  }

  
 printf("%d",a);
  
  
}