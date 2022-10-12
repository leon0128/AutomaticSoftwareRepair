#include<stdio.h>

int main(void){
  int N;
  int a;
  int b;
  char c;
  char d;
  scanf("%d",&N);
  a=N/16;
  b=N%16;
  
	if(a==10){
      c='A';
    }else if(a==11){
      c='B';
    }else if(a==12){
      c='C';
    }else if(a==13){
      c='D';
    }else if(a==14){
      c='E';
    }else if(a==15){
      c='F';
    }
  if(b==10){
      d='A';
    }else if(b==11){
      d='B';
    }else if(b==12){
      d='C';
    }else if(b==13){
      d='D';
    }else if(b==14){
      d='E';
    }else if(b==15){
      d='F';
    }
  	if(a>=10 && b>=10){
      printf("%c%c",c,d);
    }else if(a>=10 && b<10){
      printf("%c%d",c,b);
    }else if(a<10 && b>=10){
      printf("%d%c",a,d);
    }else{
      printf("%d%d",a,b);
    }
  return 0;
}
  
  