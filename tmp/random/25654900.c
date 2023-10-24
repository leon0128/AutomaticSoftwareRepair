#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int upll(const void * a, const void * b)
{
    
    return * (long long *)a < * (long long *)b ? - 1 : * (long long *)a > * (long long *)b ? 1 : 0;
}

int downll(const void * a, const void * b)
{
    
    return * (long long *)a < * (long long *)b ? 1 : * (long long *)a > * (long long *)b ? - 1 : 0;
}

void sortup(long long * a, int n)
{
    qsort(a, n, sizeof(long long), upll);
}

void sortdown(long long * a, int n)
{
    qsort(a, n, sizeof(long long), downll);
}

long long pom(long long a, long long n, int m)
{
    long long x;
    x = 1;
    
    for(a %= m;n;n /= 2)
        n & 1 ? x = x * a % m : 0, a = a * a % m;
    
    return x;
}

int main(void)
{
    int y;
    char c;
    int cnt;
    y = 0;
    cnt = 0;
    scanf("%d", & y);
    
    if(y % 4 == 0)
    {
        c = 'y';
        cnt ++;
    }
    else
        ;
    
    if(y % 100 == 0)
    {
        c = 'n';
        cnt ++;
    }
    else
        ;
    
    if(y % 400 == 0)
    {
        c = 'y';
        cnt ++;
    }
    else
        ;
    
    if(y < 1)
        c = 'n';
    else
        ;
    printf("%s\n", c == 'y' ? "YES" : "NO");
}