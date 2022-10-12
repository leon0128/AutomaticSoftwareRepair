#include<stdio.h>
int main(){
  int n,x,y;
  scanf("%d%d%d",&x,&y,&n);
  
  int cnt=0;
  int ans=0;
  
  while(cnt!=n){
   if((n-cnt)<3){
     ans+=x;
     cnt++;
   }else{
    if(y>3*x){
      ans+=3*x;
      cnt+=3;
    }else{
      ans+=y;
      cnt+=3;
    }
   }
    
  }
  
  printf("%d",ans);

return 0;
}