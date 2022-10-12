#include <stdio.h>
#include <math.h>

int main(void){
  int x,y,z;
  scanf("%d%d%d",&x,&y,&z);
  /* 即ゴールできるかの判定 */
  if(x*y<0){
    /* ハンマー取得不要 */
    printf("%d\n",abs(x));
    return 0;
  }
  if(abs(x)<abs(y)){
    /* ハンマー取得不要 */
    printf("%d\n",abs(x));
    return 0;
  }
  /* ハンマー探し */
  if(z*y>0&&abs(z)>abs(y)){
    /* ハンマーは壁の向こう */
    printf("%d\n",-1);
    return 0;
  }
  if(z*x>0){
    /* ハンマー見つかったら最短距離 */
    printf("%d\n",abs(x));
    return 0;
  }
  printf("%d\n",abs(x)+abs(z));
  
  
  return 0;
}