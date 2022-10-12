#include <stdio.h>
int main (void){
  int A,B,t1=0,t2=0,t3=0,a1=0,a2=0,a3=0,sunuke=0;
  scanf("%d %d",&A,&B);
  
  //高橋
  if(A==7){
    t1=1;t2=2;t3=4;}
  else if(A==6){
    t2=2;t3=4;}
  else if(A==5){
    t1=1;t3=4;}
  else if(A==4){
    t3=4;}
  else if(A==3){
    t1=1;t2=2;}
  else if(A==2){
    t2=2;}
  else if(A==1){
    t1=1;}
  
  //青木
    if(B==7){
    a1=1;a2=2;a3=4;}
  else if(B==6){
    a2=2;a3=4;}
  else if(B==5){
    a1=1;a3=4;}
  else if(B==4){
    a3=4;}
  else if(B==3){
    a1=1;a2=2;}
  else if(B==2){
    a2=2;}
  else if(B==1){
    a1=1;}
  
  //すぬけ
  if((t1>=1)||(a1>=1)){
    sunuke+=1;
  }
  if((t2>=1)||(a2>=1)){
    sunuke+=2;
  }
  if((t3>=1)||(a3>=1)){
    sunuke+=4;
  }
  printf("%d",sunuke);
}