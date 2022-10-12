#include <stdio.h>
int main()
{
    int count, i = 0;
    char arr[100][100];
    while (1)
    {
        scanf("%c", &arr[1][i]);

        if ((arr[1][i] == ' ') || (arr[1][i] == '\n'))
        {
            break;
        }

        i++;
    }
    i = (i / 2) ;

    for (int j = i; j < (i + 1); j++)
    {
        printf("%c\n", arr[1][j]);
    }
}
