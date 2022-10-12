#include<stdio.h>

int main(void)
{
	int a, b;
    scanf("%d %d", &a, &b);
    int ara[] = {0, 1, 2, 4};
    for (int i = 0; i < 3; i++)
    {
    	for (int j = i + 1; j < 4; j++)
        {
        	if (a == ara[i] + ara[j] && b == ara[i] + ara[j])
            {
            	printf("%d", ara[i] + ara[j]);
            }
            else
            {
            	printf("%d", a + b);
            }
        }
    }
}