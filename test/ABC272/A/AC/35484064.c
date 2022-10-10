#include<stdio.h>
#include<string.h>

int main(void)
{
	int n, sum = 0;
    scanf("%d", &n);
    int ara[n];
    for (int i = 0; i < n; i++)
    {
    	scanf("%d", &ara[i]);
    }
    for (int i = 0; i < n; i++)
    {
    	sum = sum + ara[i];
    }
    printf("%d", sum);
}