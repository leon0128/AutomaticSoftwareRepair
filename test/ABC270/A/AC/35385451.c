#include<stdio.h>
#include<math.h>
int main(){

int a,b,c,d,i;

scanf("%d %d",&c, &d);
i=c+d;
if(i==0)
{
    printf("0");
}
if(i==1)
{
    printf("1");
}
if(i==2)
{
    if(c==2&&d==0||c==0&&d==2)
    {
        printf("2");
    }

    if(c==1&&d==1)
    {
       printf("1");
    }
}
if(i==3)
{
    printf("3");
}
if(i==4)
{
    if(c==2&&d==2)
    {
        printf("2");
    }
    if(c==3&&d==1||c==1&&d==3)
    {
        printf("3");
    }
    if(c==4&&d==0||c==0&&d==4)
    {
        printf("4");
    }
}
if(i==5)
{
    if(c==2&&d==3||c==3&&d==2)
    {
        printf("3");
    }
    else
    {
        printf("5");
    }
}
if(i==6)
{
    if(c==3&&d==3)
    {
        printf("3");
    }
    if(c==5&&d==1||c==1&&d==5)
    {
        printf("5");
    }
    else
    {
        printf("6");
    }
}
if(i==7)
{
    printf("7");
}
if(i==8)
{
    if(c==4&&d==4)
    {
        printf("4");
    }
    if(c==2&&d==6||c==6&&d==2)
    {
        printf("6");
    }
    else
    {
        printf("7");
    }
}
if(i==9)
{
   if(c==4&&d==5||c==5&&d==4)
   {
       printf("6");
   }
   else
   {
       printf("7");
   }
}
if(i==10)
{
    if(c==5&&d==5)
    {
        printf("5");
    }
    if(c==6&&d==4||c==4&&d==6)
    {
        printf("6");
    }
    else
    {
        printf("7");
    }
}
if(i==11)
{
    printf("7");
}
if(i==12)
{
    if(c==7&&d==5||c==5&&d==7)
    {
        printf("7");
    }
    else
    {
        printf("6");
    }
}
if(i==13)
{
    printf("7");
}
if(i==14)
{
    printf("7");
}

printf("\n");
return 0;
}
