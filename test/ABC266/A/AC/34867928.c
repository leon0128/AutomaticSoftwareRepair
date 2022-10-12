#include<stdio.h>
#include<string.h>
int main()
{
    char arr[100];
    gets(arr);
    int d=strlen(arr);
    for(int i=0;i<d;i++)
    {
        if(i==d/2)
        {
            printf("%c",arr[i]);
        }

    }
    return 0;

}
