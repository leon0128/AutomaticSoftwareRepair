#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define _CRT_SECURE_NO_WARNINGS
#define ll long long
#define rep(i,l,r)for(ll i=(l);i<(r);i++)
#define repp(i,l,r,k)for(ll i=(l);i<(r);i+=(k))
#define INF ((1LL<<62)-(1LL<<31))
#define max(p,q)((p)>(q)?(p):(q))
#define min(p,q)((p)<(q)?(p):(q))
#define bit(n,m)(((n)>>(m))&1)
int upll(const void*a, const void*b){return*(ll*)a<*(ll*)b?-1:*(ll*)a>*(ll*)b?1:0;}
int downll(const void*a, const void*b){return*(ll*)a<*(ll*)b?1:*(ll*)a>*(ll*)b?-1:0;}
void sortup(ll*a,int n){qsort(a,n,sizeof(ll),upll);}
void sortdown(ll*a,int n){qsort(a,n,sizeof(ll),downll);}
ll pom(ll a,ll n,int m){ll x=1;for(a%=m;n;n/=2)n&1?x=x*a%m:0,a=a*a%m;return x;}
//#define MOD 998244353
#define MOD 1000000007
#define invp(a,p)pom(a,p-2,p)

// #include <ctype.h>

// #include <stdio.h>
// #include <string.h>
int main(void)
{	
	int y;
	char c = 'y';
	int cnt = 0;

	scanf("%d", &y);

	if(y % 4 == 0)
	{
		c = 'y';
		cnt++;
	}
	if(y % 100 == 0)
	{
		c = 'n';
		cnt++;
	}
	if(y % 400 == 0)
	{
		c = 'y';
		cnt++;
	}
	if(y < 1) c = 'n';

	printf("%s\n", c == 'y' ? "YES" : "NO");
}