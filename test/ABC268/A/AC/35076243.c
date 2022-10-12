#include <stdio.h>

int main(void)
{
    int num[5];
    int tmp;
    int count = 5;
    int i;
    int j;

    scanf("%d %d %d %d %d", &num[0], &num[1], &num[2], &num[3], &num[4]);

    i = 0;
    while (i < 5)
    {
        tmp = num[i];
        j = i + 1;
        while (j < 5)
        {
            if (tmp == num[j])
            {
                count--;
                break;
            }
            j++;
        }
        i++;
    }
    printf("%d\n", count);

    return 0;
}