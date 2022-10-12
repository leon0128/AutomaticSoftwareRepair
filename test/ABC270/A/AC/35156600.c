#include <stdio.h>
int main()
{
  int A,B,C,a[3],b[3];

  scanf("%d",&A);
  scanf("%d",&B);
  
    a[0]=A/4;
    A=A%4;
    a[1]=A/2;
    A=A%2;
    a[2]=A;

    b[0]=B/4;
    B=B%4;
    b[1]=B/2;
    B=B%2;
    b[2]=B;

    C=0;

    if(a[0]==1 || b[0]==1)
      C+=4;
    if(a[1]==1 || b[1]==1)
      C+=2;
    if(a[2]==1 || b[2]==1)
      C+=1;

    printf("%d\n",C);

    return 0;
}