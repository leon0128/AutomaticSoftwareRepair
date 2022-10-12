#include<stdio.h>
int main()
{
    char a[10];
    scanf("%s",a);
    if(a[2]=='n') printf("5\n");
    else if(a[2]=='e') printf("4\n");
    else if(a[2]=='d') printf("3\n");
    else if(a[2]=='u') printf("2\n");
    else printf("1\n");
}
