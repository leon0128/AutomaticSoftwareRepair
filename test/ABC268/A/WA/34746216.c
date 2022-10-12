#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num[5];
    int count = 0;
    int x = 0;
    int y = 1;
    int p[5];
    (void)scanf("%d %d %d %d %d", &num[0], &num[1], &num[2], &num[3], &num[4]);
    int sum = num[0] + num[1] + num[2] + num[3] + num[4];

    for(int i = 0; i < 5; ++i)
    {
        for(int j = 0; j < 5; ++j)
        {
            if(i != j && num[i] == num[j])
            {
                ++count;
                p[x] = num[i];
                break;
            }
        }

        for(int k = 0; k < 5; ++k)
        {
            if(num[k] == p[x])
            {
                num[k] = sum + y;
                ++y;
            }
        }
        ++x;
    }

    printf("%d", count);

}
