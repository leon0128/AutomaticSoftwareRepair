#include<stdio.h>
#include<string.h>
int main()
{
    char name[20];
    gets(name);
    if(strcmp(name,"Monday")==0)
    {
        printf("5");
    }

    else if(strcmp(name,"Tuesday")==0)
    {
        printf("4");
    }

    else if(strcmp(name,"Wednesday")==0)
    {
        printf("3");
    }
    else if(strcmp(name,"Thursday")==0)
    {
        printf("2");
    }

    else if(strcmp(name,"Friday")==0)
    {
        printf("1");
    }




    return 0;
}
