#include<stdio.h>

int main()
{
    char c;
    scanf("%c",&c);
    
    if(c=='M')
    {
        printf("5");
    }

    else if(c=='T')
    {
        char d;
        scanf("%c",&d);

        if(d=='u')
        {
            printf("4");
        }

        else
        {
            printf("2");
        }
        
    }

    else if(c=='W')
    {
        printf("3");
    }

    else if(c=='F')
    {
        printf("1");
    }

    if(c=='S')
    {
        char d;
        scanf("%c",&d);

        if(d=='u')
        {
            printf("6");
        }

        else
        {
            printf("7");
        }
    }

    return 0;
}