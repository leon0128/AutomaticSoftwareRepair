
#include <stdio.h>

#define true 1
#define false 0

int main(void){
  int y;
  scanf("%d",&y);
  _Bool sw = false;
  if (!(y%4))sw=true;
  if (!(y%100))sw=false;
  if (!(y%400))sw=true;

  if(sw){
    puts("YES");
  }else{
    puts("NO");
  }
}