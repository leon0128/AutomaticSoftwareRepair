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
#define rep(i, n) for (i = 0; i < n; i++)
#define repp(i, l, r) for (ll i = (l); i < (r); i++)

typedef long long ll;
typedef unsigned int uint;

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

int upll(const void *a, const void *b)
{
   return *(ll *)a < *(ll *)b ? -1 : 1;
}
int downll(const void *a, const void *b)
{
   return *(ll *)a < *(ll *)b ? 1 : -1;
}

void sortup(ll *a, int n) { qsort(a, n, sizeof(ll), upll); }
void sortdown(ll *a, int n) { qsort(a, n, sizeof(ll), downll); }

void swap(int *a, int *b)
{
   int c;
   c = (*a);
   (*a) = (*b);
   (*b) = c;
}

void lenplus(char s[])
{
   int len = strlen(s);
   for (int i = len; i >= 0; i--)
      s[i + 1] = s[i];
}

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

ll Gcd(ll m, ll n)
{
   ll r;

   while (n > 0)
   {
      r = m % n;
      m = n;
      n = r;
   }
   return m;
}

ll Lcm(ll a, ll b)
{
   return a * b / (Gcd(a, b));
}

ll nPr(int n, int r)
{
   ll i, result = 1;
   rep(i, r) { result *= (ll)(n - i); }
   return result;
}

int nCr(int n, int r)
{
   int i, result = 1;
   rep(i, MIN(r, n - r))
   {
      result *= (int)(n - i);
      result /= (int)(i + 1);
   }
   return result;
}

ll change_radix(ll x, ll y)
{
   ll new = 0, cnt = 1;
   do
   {
      new += (x % y) * cnt;
      x /= y;
      cnt *= 10;
   } while (x > 0);
   return new;
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
   int h, w, i, j, x = 1, y = 1;
   char g[501][501];
   scanf("%d%d", &h, &w);

   for (i = 1; i <= h; i++)
      scanf("%s", g[i]);

   puts("");

   for (i = 1; i <= h; i++)
      printf("%s\n", g[i]);

   for (i = 1; i <= h; i++)
   {
      for (j = w; j >= 0; j--)
      {
         g[i][j] = g[i][j - 1];
      }
   }

   int cnt = 0;

   do
   {
      if (g[x][y] == 'U' && x != 1)
         x -= 1;
      else if (g[x][y] == 'D' && x != h)
         x += 1;
      else if (g[x][y] == 'L' && y != 1)
         y -= 1;
      else if (g[x][y] == 'R' && y != w)
         y += 1;
      else
      {
         printf("%d %d", x, y);
         exit(0);
      }

      cnt++;

   } while (cnt <= 10000000);
   printf("%d", -1);
   return 0;
}