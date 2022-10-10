#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long LL;
typedef int T;
#define max(A,B)	({ __typeof__(A) __a = (A); __typeof__(B) __b = (B); __a > __b ? __a : __b; })
#define min(A,B)	({ __typeof__(A) __a = (A); __typeof__(B) __b = (B); __a < __b ? __a : __b; })
#define swap(A, B)  { __typeof__(A) __temp = A; A = B; B = __temp;}  //传入的参数只支持变量，不能支持表达式，因为有语句“A = B; B = __temp;”
T mycmp(const void* a, const void* b);
int read(void);
/*******************************/

int main(void)
{
    setvbuf(stdout, calloc(1 << 20, sizeof(char)), _IOFBF, 1 << 20);

    int n = read();
    int a[n];
    int sum = 0;
    for(int i=0; i<n; i++)
        sum+=read();
    printf("%d", sum);
}


/********************************/
T mycmp(const void* a, const void* b)
{
    return *(T*)a-*(T*)b;
}
int read(void)
{
    int s = 0, f = 1;
    char ch = getchar();
    while(ch < &#39;0&#39; || ch > &#39;9&#39;)
    {
        if(ch == &#39;-&#39;)
            f = -1;
        ch = getchar();
    }
    while(ch >= &#39;0&#39; && ch <= &#39;9&#39;)
    {
        s = s * 10 + ch - &#39;0&#39;;
        ch = getchar();
    }
    return s * f;
}
