#include<stdio.h>
int main(){
  int A,B,C;
  scanf("%d %d",&A,&B);
  
  int score[3][2] ={{0,0,0},{0,0,0}};
  int i;

  switch(A){
    case 1:
      score[0][i]=1;
      break;
    case 2:
      score[1][i]=1;
      break;
    case 3:
      score[0][i]=1;
      score[1][i]=1;
      break;
    case 4:
      score[2][i]=1;
      break;
    case 5:
      score[0][i]=1;
      score[2][i]=1;
      break;
    case 6:
      score[1][i]=1;
      score[2][i]=1;
      break;
    case 7:
      score[0][i]=1;
      score[1][i]=1;
      score[2][i]=1;
      break;
  }
  switch(B){
    case 1:
      score[0][i]=1;
      break;
    case 2:
      score[1][i]=1;
      break;
    case 3:
      score[0][i]=1;
      score[1][i]=1;
      break;
    case 4:
      score[2][i]=1;
      break;
    case 5:
      score[0][i]=1;
      score[2][i]=1;
      break;
    case 6:
      score[1][i]=1;
      score[2][i]=1;
      break;
    case 7:
      score[0][i]=1;
      score[1][i]=1;
      score[2][i]=1;
      break;
  }
  
    //printf("%d:%d,%d\n",1,score[0][0],score[0][1]);
    //printf("%d:%d,%d\n",2,score[1][0],score[1][1]);
    //printf("%d:%d,%d\n",4,score[2][0],score[2][1]);
  
  C=0;
  if (score[0][0]+score[0][1]==1) C=C+1;
  if(score[1][0]+score[1][1]==1) C=C+2;
  if(score[2][0]+score[2][1]==1) C=C+4;
  
  printf("%d",C);
  return 0;
}