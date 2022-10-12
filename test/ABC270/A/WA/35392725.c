#include<stdio.h>

int main()
{
int A,B,C;
scanf("%d%d",&A,&B);
if((A>=0&&A<=7)&&(B>=0&&B<=7))
{
if(A==0 && B==0){
C=0;
printf("%d",C);
}

else if(A==B){
C=A;
printf("%d",C);
}
else if(A==7||B==7){
C=7;
printf("%d",C);
}

else if((B==1||B==2||B==4)&&(A!=1||A!=2||A!=4)&&(A!=B))
{ 
C=B+A;
printf("%d",C);
}

else if((A==1||A==2||A==4)&&(A!=B)){
C=B;
printf("%d",C);
}
else if((A!=1||A!=2||A!=4)&&((B!=1||B!=2||B!=4))&&(A!=B))
{
C=7;
printf("%d",C);
}

else if((A==1||A==2||A==4)&&((B!=1||B!=2||B!=4))&&(A!=B)){
C=B+A;
printf("%d",C);
}
else if((B==1||B==2||B==4)&&(A!=B)){
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
}
    return 0;
}