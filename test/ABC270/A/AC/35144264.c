#include<stdio.h>
int main(void)
{
  int A,B,C=0;
  int Q1=0,Q2=0,Q3=0;
  scanf("%d",&A);
  scanf("%d",&B);
  
  if(A>=4){
    Q1=1;
    A-=4;}
  
  if(A>=2){
    Q2=1;
    A-=2;}
  
  if(A>=1){
    Q3=1;}
  
  if(B>=4){
    Q1=1;
    B-=4;}
  
  if(B>=2){
    Q2=1;
    B-=2;}
  
  if(B>=1){
    Q3=1;}
  
  
  if(Q1==1){C+=4;}
  if(Q2==1){C+=2;}
  if(Q3==1){C+=1;}
    printf("%d",C);
}