#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#define INF ((1LL<<62)-(1LL<<31))
#define MOD 1000000007
#define rep(i,l,r) for(int i=(l);i<(r);i++)
#define max(p,q) ((p)>(q)?(p):(q))
#define min(p,q) ((p)<(q)?(p):(q))

int main(void)
{
	int n;
	int a,b;

	scanf("%d",&n);
	a = n/16;
	b = n%16;
	if (a < 10) printf("%d",a);
	else if(a == 10) printf("A");
	else if(a == 11) printf("B");
	else if(a == 12) printf("C");
	else if(a == 13) printf("D");
	else if(a == 14) printf("E");
	else if(a == 15) printf("F");
	if (b < 10) printf("%d",b);
	else if(b == 10) printf("A");
	else if(b == 11) printf("B");
	else if(b == 12) printf("C");
	else if(b == 13) printf("D");
	else if(b == 14) printf("E");
	else if(b == 15) printf("F");

	return (0);
}