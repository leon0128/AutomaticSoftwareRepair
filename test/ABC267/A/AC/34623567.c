#include<stdio.h>
int main()
{
    char a[20],i,n;
    gets(a);

    if(a[0]=='S'&&a[1]=='a')
        printf("7\n");
    else if(a[0]=='S'&&a[1]=='u')
        printf("6\n");
    else if(a[0]=='M')
        printf("5\n");
    else if(a[0]=='T'&&a[1]=='u')
        printf("4\n");
    else if(a[0]=='W')
        printf("3\n");
    else if(a[0]=='T'&&a[1]=='h')
        printf("2\n");
    else if(a[0]=='F')
        printf("1\n");
}
