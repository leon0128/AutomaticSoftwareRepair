#include <stdio.h>

int main(){
   int n;

   scanf("%d",&n);
   if (n<16) printf("0%X\n",n);
   else      printf("%X\n",n);
   return 0;
}