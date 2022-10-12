#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
long long int N,P,Q,R;
long long int i;
long long int A[230000];
long long int S[230000];

int main(){
scanf("%lld %lld %lld %lld",&N,&P,&Q,&R);
for(i=0;i<N;i++)
scanf("%lld",&A[i]);

S[0]=0;
for(i=0;i<N;i++)
S[i+1]=S[i]+A[i];


long long int x,y,z,w;
long long int mid,min,max;
//else if(S[mid]-S[x]>=P)とするとxの値が大きくなったときの
//マイナスの値を考慮できない？

for(x=0;x<N;x++){
  min=x;
  max=N;
  while(max-min>1){
    mid=(min+max)/2;
    if(S[mid]-S[x]<P)
      min=mid;
    else if(S[mid]-S[x]>=P)
      max=mid;
  }
  y=max;
  min=y;
  max=N;
  while(max-min>1){
    mid=(min+max)/2;
    if(S[mid]-S[y]<Q)
      min=mid;
    else if(S[mid]-S[y]>=Q)
      max=mid;
  }
  z=max;
  min=z;
  max=N;
  while(max-min>1){
    mid=(min+max)/2;
    if(S[mid]-S[z]<R)
      min=mid;
    else if(S[mid]-S[z]>=R)
      max=mid;
  }
  w=max;
  if(S[y]-S[x]==P && S[z]-S[y]==Q && S[w]-S[z]==R){
    printf("Yes");
    return 0;
  }
}
printf("No");
 return 0;
}