

#include <stdio.h>

int main()
{
   int a,b,c,total;
   scanf("%d",&a);
   scanf("%d",&b);
   scanf("%d",&c);
   
   int three=c/3;
   int one=c-(3*three);
  
   
   total=(three*b)+(one*a);
   int conf=a*c;
   
   if(total<conf){
       printf("%d",total);
   }
   else{
       printf("%d",conf);
   }

    return 0;
}
