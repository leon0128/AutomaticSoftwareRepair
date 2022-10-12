#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

#define Yes() puts("Yes")
#define No() puts("No")
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define JUD(x) (x) == 1 ? Yes() : No()
#define ABS(x) (x) < 0 ? -(x) : (x)
#define ABSS(x, y) (x) > (y) ? (x) - (y) : (y) - (x)
#define rep(i, n) for (int i = 0; i < (n); ++i)

typedef long long ll;
typedef unsigned int uint;

int fact(int n)
{
   return (n == 1 ? 1 : n * fact(n - 1));
}

int DigitSum(int a)
{
   int x = 0;
   do
   {
      x += a % 10;
      a /= 10;
   } while (a > 0);
   return x;
}

int round_up(int a, int b)
{
   return (a + b - 1) / b;
}

int charcmp(const void *a, const void *b)
{
   return *(const char *)a - *(const char *)b;
}

int charcmprev(const void *a, const void *b)
{
   return *(const char *)a - *(const char *)b;
}

int intcmp(const void *a, const void *b)
{
   return *(const int *)a - *(const int *)b;
}

int intcmprev(const void *a, const void *b)
{
   return *(const int *)b - *(const int *)a;
}

void merge_sort(int n, int x[])
{
   static int y[200001] = {};
   if (n <= 1)
      return;
   merge_sort(n / 2, &(x[0]));
   merge_sort((n + 1) / 2, &(x[n / 2]));

   int i, p, q;
   for (i = 0, p = 0, q = n / 2; i < n; i++)
   {
      if (p >= n / 2)
         y[i] = x[q++];
      else if (q >= n)
         y[i] = x[p++];
      else
         y[i] = (x[p] < x[q]) ? x[p++] : x[q++];
   }
   for (i = 0; i < n; i++)
      x[i] = y[i];
}

int main()
{
   int a, b, c, d;
   scanf("%d%d%d%d", &a, &b, &c, &d);
   printf("%d\nTakahashi", (a + b) * (c - d));
   return 0;
}