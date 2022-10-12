#include<stdio.h>
#include<math.h>


void main(){
  
  int ax, ay;
  int bx, by;
  int cx, cy;
  int dx, dy;
  
  double m1, n1;
  double m2, n2;
  double kai_x, kai_y;
  
  scanf("%d %d\n", &ax, &ay);
  scanf("%d %d\n", &bx, &by);
  scanf("%d %d\n", &cx, &cy);
  scanf("%d %d\n", &dx, &dy);
  
  m1 = (double)(cy-ay)/(double)(cx-ax);
  m2 = (double)(dy-by)/(double)(dx-bx);
  n1 = ay-m1*ax;
  n2 = by-m2*bx;
  
  kai_x = - (n2-n1)/(m2-m1);
  kai_y = m1*kai_x+n1;
  

  if( ax < kai_x && kai_x < cx ){
    if( ay < kai_y && kai_y < cy ){
      printf("Yes\n");
      return;
    }
  }
  printf("No\n");
  
  return;
}
