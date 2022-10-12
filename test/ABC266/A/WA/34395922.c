#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int main(void){

long long int N;
long long int M;
long long int Ans;

scanf("%lld",&N);

if(0<N && N<998244353){
  Ans=998244353-N;
  printf("%lld",Ans);
  return 0;
}

else if(-998244353<N && N<0){
  Ans=998244353+N;
  printf("%lld",Ans);
  return 0;
}

else if(N>0){
M=N/998244353;
Ans=N-998244353*M;
printf("%lld",Ans);
return 0;
}

else if(N<0){
M=N/998244353;
Ans=N-(M-1)*998244353;
printf("%lld",Ans);
return 0;
}
else if(N==0){
  Ans=0;
  printf("%lld",Ans);
  return 0;
}

  return 0;
}