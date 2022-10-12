#include<stdio.h>

void check (int a,int q1,int q2, int q3){
if(a%2==1){
  q1= 1;}
  else{
  q1=0;
  }
  if(a==2||a==3||a==6||a==7){
  q2= 1;}
  else{
  q2=0;
  }
  if(a>3){
  q3= 1;}
  else{
  q3=0;
  }
  
  printf("check/1=%d,2=%d,3=%d\n",q1,q2,q3);
}
  


int main (){
int a,b,c;
  c=0;
  int a1,a2,a3,b1,b2,b3;
  scanf("%d%d",&a,&b);
 // check(a,a1,a2,a3);
 // check(b,b1,b2,b3);
  
  if(a%2==1){
  a1= 1;}
  else{
  a1=0;
  }
  if(a==2||a==3||a==6||a==7){
  a2= 1;}
  else{
  a2=0;
  }
  if(a>3){
  a3= 1;}
  else{
  a3=0;
  }
  
  if(b%2==1){
  b1= 1;}
  else{
  b1=0;
  }
  if(b==2||b==3||b==6||b==7){
  b2= 1;}
  else{
  b2=0;
  }
  if(b>3){
  b3= 1;}
  else{
  b3=0;
  }
  
  
  if(a1==0&&b1==0){
  }
  else{
  c+=1;}
    if(a2==0&&b2==0){
  }
  else{
  c+=2;}
   if(a3==0&&b3==0){
  }
  else{
  c+=4;} 
  
printf("%d\n",c);  
}