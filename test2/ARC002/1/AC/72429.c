#include <stdio.h>
#include <stdlib.h>

int main(void){
  int year;

  scanf("%d",&year);

  if(year % 4 == 0 ){
    if(year % 100 == 0){
      if(year % 400 == 0){
	printf("YES\n");
	exit(0);
      }
      printf("NO\n");
      exit(0);
    }
    printf("YES\n");
  }else{
    printf("NO\n");
  }

  return 0;
}
