#include <stdio.h>

int main() {
   int x,y;
   int  N;
    scanf("%d",&x);
  scanf("%d",&y);
    scanf("%d",&N);
   int n,p;
    n=N/3;
    p=N%3;
    


   if(N%3==0){
       int output=y*n;
       printf("%d",output);
   }
   else {
       int output = (y* n) + (x* p);
       printf("%d", output);
   }

}
