#include <stdio.h>

int main(){
   int i,n,a,s;

   scanf("%d",&n);
   for (s=i=0;i<n;i++) {
      scanf("%d",&a);
      s+=a;
   }
   printf("%d\n",s);
   return 0;
}
