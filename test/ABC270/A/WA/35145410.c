#include<stdio.h>

int main()

{

   int a,b;

scanf("%d%d",&a,&b);

if(b>a)

{

  int temp=b;

   b=a;

  a=temp;

}

printf("%d\n",2*a-b);

        return 0;

}