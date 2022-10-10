#include<stdio.h>
#define ll long long
int main(int argc, char** argv){
	ll n, i, j, sum = 0;
  	scanf("%lld", &n);
  
  	for(i = 0;i<n;i++){
    	scanf("%lld", &j);
      	sum+=j;
    }printf("%lld", sum);
}