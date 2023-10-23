#include<stdio.h>

int main(void)
{
    char *str = "NO";
    int year;

    // 年度の入力
    scanf("%d", &year);

    if( year % 4 == 0 )
    {
        str = "YES";

        if( year % 100 == 0 )
        {
            str = "NO";

            if( year % 400 == 0 )
            {
                str = "YES";
            }
        }
    }

    printf("%s\n", str);

    return 0;
}
