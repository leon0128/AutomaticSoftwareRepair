#include<stdio.h>

int main()
{
int A,B,C,d,e,f,g,h,i;
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
scanf("%d%d%d",&d,&e,&f);
A=d+e+f;
scanf("%d%d%d",&g,&h,&i);
B=g+h+i;
C=A-B;
printf("%d",C);
}


    return 0;
}