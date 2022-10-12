#include<stdio.h>
int main(void)
{
  int A=0,B=0,sunu=0,toi1=0,toi2=0,toi4=0;
  scanf("%d %d",&A,&B);
  if(A==1)toi1=1;
  else if(A==2)toi2=1;
  else if(A==4)toi4=1;
  else if(A==3){
    toi1=1;
    toi2=1;
  }
  else if(A==5){
    toi1=1;
    toi4=1;
              }
  else if(A==6){
    toi2=1;
    toi4=1;
  }
  else if(A==7){
    toi1=1;
    toi2=1;
    toi4=1;
  }
  if(B==1)toi1=1;
  else if(B==2)toi2=1;
  else if(B==3){
    toi1=1;
    toi2=2;
  }
  else if(B==4)toi4=4;
  else if(B==5){
    toi4=1;
    toi1=1;
  }
  else if(B==6){
    toi2=1;
    toi4=1;
  }
  else if(B==7){
    toi1=1;
    toi2=1;
    toi4=1;
  }
  if(toi1==1)sunu=sunu+1;
  if(toi2==1)sunu=sunu+2;
  if(toi4==1)sunu=sunu+4;
  printf("%d",sunu);
  return 0;
}