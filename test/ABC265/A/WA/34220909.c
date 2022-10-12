

#include <stdio.h>

int main()
{
   int a,b,c,total=0;
   scanf("%d",&a);
   scanf("%d",&b);
   scanf("%d",&c);
   
   int three=c/3;
   int one=c-(3*three);
  
   
   total=(three*b)+(one*a);
   printf("%d",total);

    return 0;
}
