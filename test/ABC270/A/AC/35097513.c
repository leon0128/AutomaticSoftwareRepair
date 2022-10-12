#include <stdio.h>

int main(){
   int a,b,c;

   scanf("%d %d",&a,&b);
   if (a%2==1 || b%2==1) c=1;
   else                  c=0;
   if ((a&2)==2 || (b&2)==2) c+=2;
   if ((a&4)==4 || (b&4)==4) c+=4;
   printf("%d\n",c);
   return 0;
}