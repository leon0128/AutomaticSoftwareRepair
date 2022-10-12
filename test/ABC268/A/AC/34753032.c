#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num[5];
    int count = 5;
    int y = 1;
    (void)scanf("%d %d %d %d %d", &num[0], &num[1], &num[2], &num[3], &num[4]);
    int sum = num[1] + num[2] + num[3] + num[4] + num[0];

    for(int i = 0; i < 5; ++i)
    {
        for(int j = 0; j < 5; ++j)
        {
            if(i != j && num[i] == num[j])
            {
                --count;
                num[j] = sum + y;
                ++y;
            }
        }



    }

    printf("%d", count);

}
