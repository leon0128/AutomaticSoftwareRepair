

#include<stdio.h>
main(){
  int n,co = 0;
  scanf("%d",&n);
  if(n % 4 == 0){
    if(n % 100 == 0){
      if(n % 400 == 0){
	co = 1;
      }
      co = 0;
    }
    co = 1;
  }
  if(co == 1)puts("YES");
  else puts("NO");
  return 0;
}
