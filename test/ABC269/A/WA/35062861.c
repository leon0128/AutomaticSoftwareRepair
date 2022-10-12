#include<stdio.h>

int main(){

    int a,b,c,d,sum;

    char str[20];

    scanf("%d%d%d%d",&a,&b,&c,&d);

    scanf("%s",str);

    sum=(a+b)*(c-d);

    printf("%d\n%s\n",sum,str);



return 0;

}
