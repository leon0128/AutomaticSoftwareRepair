#include<stdio.h>

int main()
{
int A,B,C;
scanf("%d%d",&A,&B);
if (A==B){
C=A;
printf("%d",C);
}
else if ((A==1||A==2||A==4)&&(B==1||B==2||B==4)&&(A!=B))
{
C=A+B;
printf("%d",C);
}
else
{
C=A-B;
C=C+A;
printf("%d",C);
}
    return 0;
}
