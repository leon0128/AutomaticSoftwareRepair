#include <stdio.h>
int main(){
   int x,y,z,num=0,num1=0,num2=0,i,num3=0;
   scanf("%d %d %d",&x,&y,&z);
   num = z/3;
   num1 = z%3;
   for(i=0;i<z;i++){
      num3 += x;
   }
   for(i=0;i<num;i++){
      num2 += y;
   }
   for(i=0;i<num1;i++){
      num2 += x;
   }
   if(num3<num2){
      printf("%d",num3);
   }
   else{
      printf("%d",num2);
   }
}