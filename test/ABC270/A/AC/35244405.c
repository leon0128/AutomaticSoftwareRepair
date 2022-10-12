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
	int a,b;
	int ans;

	scanf("%d %d",&a,&b);

	ans = a | b;
	
	printf("%d\n",ans);

	return (0);
}