#include <stdio.h>
#include <stdlib.h>

int main()
{
    char day1,day2;
    scanf ("%c%c",&day1,&day2);
    
    if(day1==77)//"M"
    {
        printf("5\n");
    }
    else if(day1==87)//"W"
    {
        printf("3\n");
    }
    else if(day1==70)//"F"
    {
        printf("1\n");
    }
    else
    {
        if(day2==117)//"u"
            {
                printf("4\n");\
            }
        else
            {
                printf("2\n");
            }
    }





    return 0;
}
