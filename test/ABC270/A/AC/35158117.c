#include<stdio.h>
int main(void){
  int a,b,c;
  scanf("%d %d",&a,&b);
  c=0;
  if(a==1||b==1||a==3||b==3||a==5||b==5||a==7||b==7) c+=1;
  if(a==2||b==2||a==3||b==3||a==6||b==6||a==7||b==7) c+=2;
  if(a==4||b==4||a==5||b==5||a==6||b==6||a==7||b==7) c+=4;
  printf("%d\n",c);
}