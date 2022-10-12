#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#define FOR(i,n) for(ll i=0;i<n;i++)
#define PRN(n) printf("%d\n",n)
#define PRF(n) printf("%.10lf\n",n)
#define PRL(n) printf("%lld\n",n)
#define PRS(s) printf("%s\n",s)
#define PRC(c) printf("%c",c)
#define INF 10000000000
#define PI 3.1415926535
#define mod 1000000007
typedef long long int ll;
char yesno[2][4]={"No","Yes"};
ll usort(const void *a, const void *b){return *(ll*)a-*(ll*)b;}
ll dsort(const void *a, const void *b){return *(ll*)b-*(ll*)a;}
ll ssort(const void *a, const void *b){return strcmp((char*)a,(char*)b);}
int ini(){
  int n;
  scanf("%d",&n);
  return n;
}
ll inl(){
  ll n;
  scanf("%lld",&n);
  return n;
}
double inlf(){
  double n;
  scanf("%lf",&n);
  return n;
}
void Iswap(ll *a,ll *b){
  ll t=*a;
  *a=*b;
  *b=t;
}
void Fswap(double *a,double *b){
  double t=*a;
  *a=*b;
  *b=t;
}
ll min(ll a,ll b){
  if(a>b)return b;
  return a;
}
ll max(ll a,ll b){
  if(a>b)return a;
  return b;
}
ll z(ll a){return max(a,-a);}
ll gcd(ll a,ll b){if(!b)return a;return gcd(b,a%b);}
ll lcm(ll a,ll b){return a*b/gcd(a,b);}
ll kt(ll a){
  ll sum=0;
  while(a){
    a/=10;
    sum++;
  }
  return sum;
}
ll ks(ll a){
  ll sum=0;
  while(a){
    sum+=a%10;
    a/=10;
  }
  return sum;
}
ll modpow(ll a,ll n,ll m){
  ll res=1;
  while(n>0){
    if(n&1)res=res*a%m;
    a=a*a%m;
    n>>=1;
  }
  return res;
}
void divprint(ll a){
  ll x[100000];
  ll cnt=0;
  for(ll i=1;i*i<=a;i++){
    if(a%i<1){
      if(a-i*i)x[cnt++]=a/i;
    }
  }
  FOR(i,cnt)PRL(x[cnt-i-1]);
}
ll divcnt(ll a){
  ll cnt=0;
  for(ll i=1;i*i<=a;i++){
    if(a%i<1){
      cnt++;
      if(a-i*i)cnt++;
    }
  }
  return cnt;
}

int main(void){
  char s[110];
  scanf("%s",s);
  int l=strlen(s);
  PRC(s[l/2]);

  
  
  
  
  
  
  
  return 0;
}
