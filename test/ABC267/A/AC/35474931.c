#include<stdio.h>
int main()
{
    char first;

    first=getchar();
    switch(first)
    {
        case 'W':
        printf("3");
        break;
        case 'M':
        printf("5");
        break;     
        case 'F':
        printf("1");
        break;
        case 'T':
        first=getchar();
        if(first=='u')
        printf("4");
        else
        printf("2");          
    }
    return 0;
}