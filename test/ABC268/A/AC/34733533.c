#include <stdio.h>

int main(){
   int i,j,k,a[5],c[5];

   for (i=0;i<5;i++) scanf("%d",&a[i]);
   c[0]=a[0];
   for (i=j=0;i<5;i++) {
      for (k=0;c[k]!=a[i] && k<j;k++) ;
      if (k==j) c[j++]=a[i];
   }
   printf("%d\n",j);
   return 0;
}
