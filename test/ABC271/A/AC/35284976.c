#include <stdio.h>
int main(){
   int i=0,j=0,n;
   char henkan[16] = "0123456789ABCDEF";
   char answer[10];
   scanf("%d",&n);
   if(n==0){
    printf("00\n");
   }else{
   while(n>0){
    j=n%16;
    n/=16;
    answer[i]=henkan[j];
    i++;
   }
   i--;
   if(i==0){
    answer[1]='0';
    i++;
   }
  
   for(j=i;j>=0;j--){
    printf("%c",answer[j]);
   }
   printf("\n");
   }
   

    return 0;
}