#include <stdio.h>
int main(int argc, char const *argv[])
{
    int y;
    //printf("y ->");
    scanf("%d", &y);

    if (y % 4 == 0)
    {
        if (y % 100 != 0)
        {
            printf("YES\n");
        }
        else if (y % 400 == 0)
        {
            printf("YES\n");
        }else
        {
            printf("NO\n");
        }
        
    }
    else
    {
        printf("NO\n");
    }

    return 0;
}
