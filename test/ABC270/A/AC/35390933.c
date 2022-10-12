#include <stdio.h>
int main()
{
    int a,b,c,d;
    scanf("%d %d",&a,&b);
  if (a==7 || b==7)
  {
      c=7;
      printf("%d",c);
      }
      if (a<7 && a>0 && b>0 && b<7)
      {
       if ((a==1 && b==2) || (a==2 && b==1))
       {
           c=3;
           printf("%d",c);
       }
       if ((a==1 && b==3) || (a==3 && b==1))
       {
           c=3;
           printf("%d",c);
       }
       if ((a==1 && b==4) || (a==4 && b==1))
       {
           c=5;
           printf("%d",c);
       }
       if ((a==1 && b==5) || (a==5 && b==1))
       {
           c=5;
           printf("%d",c);
       }
       if ((a==1 && b==6) || (a==6 && b==1))
       {
           c=7;
           printf("%d",c);
       }
       if ((a==1 && b==6) || (a==6 && b==1))
       {
           c=7;
           printf("%d",c);
       }
       if ((a==2 && b==3) || (a==3 && b==2))
       {
           c=3;
           printf("%d",c);
       }
       if ((a==2 && b==4) || (a==4 && b==2))
       {
           c=6;
           printf("%d",c);
       }
       if ((a==2 && b==5) || (a==5 && b==2))
       {
           c=7;
           printf("%d",c);
       }
       if ((a==2 && b==6) || (a==6 && b==2))
       {
           c=6;
           printf("%d",c);
       }
       if ((a==3 && b==4) || (a==4 && b==3))
       {
           c=7;
           printf("%d",c);
       }
        if ((a==3 && b==5) || (a==5 && b==3))
       {
           c=7;
           printf("%d",c);
       }
       if ((a==3 && b==6) || (a==6 && b==3))
       {
           c=7;
           printf("%d",c);
       }
         if ((a==4 && b==5) || (a==5 && b==4))
       {
           c=5;
           printf("%d",c);
       }
       if ((a==4 && b==6) || (a==6 && b==4))
       {
           c=6;
           printf("%d",c);
       }
       if ((a==5 && b==6) || (a==6 && b==5))
       {
           c=7;
           printf("%d",c);
       }
       if( a==b)
       {

           c=a;
           printf("%d",c);
       }
       }
       if( a==0 && b!=0) { printf("%d",b);  }
       if( b==0 && a!=0) { printf("%d",a);  }
       if(a==0 && b==0) { printf("%d",a);  }
       return 0;
}
