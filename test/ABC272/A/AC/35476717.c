#include <stdio.h>
int main(){
  int t,sum=0;
  scanf("%d",&t);
  while(t--){
		int x;
		scanf("%d",&x);
    	sum+=x;
  }
  printf("%d",sum);
  return 0;
}