#include<stdio.h>
int main()
{
    char a[20];
    int i;
    scanf("%s", a);
    if(a[0]=='M')
        printf("5\n");
    else if(a[0]=='T')
    {
        if(a[1]=='u')
            printf("4\n");
        else
            printf("2\n");
    }
    else if(a[0]=='W')
        printf("3\n");
    else if(a[0]=='F')
        printf("1\n");

    return 0;
}
