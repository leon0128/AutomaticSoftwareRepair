#include <string.h>
#include <stdio.h>

int n, x;
int main(void) {
    scanf("%d", &n);
  for(int i = 0; 0 <= x; i++){
  	x = n - 998244353*i ;
    if(0 <= x || x < 998244353){
    	printf("%d", x);
      	return 0;
    }
  }
  
  for(int i = 0; x < 998244353; i--){
  	x = n - 998244353*i ;
    if(0 <= x || x < 998244353){
    	printf("%d", x);
      	return 0;
    }
  }
}