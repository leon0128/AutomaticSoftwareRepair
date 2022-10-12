#include <stdio.h>
int e[3] = {1,2,4};
int cal_point(int A, int i){
  
  int buf;
  int p[3];
  buf = A;
  
  // 4
  if(buf >=e[2]){
    p[2] = 1;
    buf -= e[2];
  }else{
    p[2] = 0;
  }
  // 2
  if(buf >= e[1]){
    p[1] = 1;
    buf -= e[1];
  }else{
    p[1] = 0;
  }
  // 1
  if(buf >= e[0]){
    p[0] = 1;
  }else{
    p[0] = 0;
  }
  
  //printf("%d%d%d\n", p[2], p[1], p[0]);
  return p[i];

}
  


int main(void){
  
  int i;
  int A,B,C;
  int pA[3], pB[3], pC[3];
  
  // input
  scanf("%d %d", &A, &B);
  
  // cal
  C = 0;
  for(i=0; i<=2; i++){
    pA[i] = cal_point(A, i);
    pB[i] = cal_point(B, i);
    
    pC[i] = pA[i] || pB[i];
    C += pC[i]*e[i];
  }
  
  // out
  printf("%d", C);

  
}