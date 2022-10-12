#include<stdio.h>
#include<string.h>
int main()
{
	int a[101],b[101],n,i=0;
  	memset(b,0,sizeof(b));
  	while(scanf("%d",&n)!=EOF){
      a[i++]=n;
    }
  	for(int j=0;j<i;j++){
      b[a[j]]++;
    }
  int cnt=0;
  for(int j=0;j<101;j++){
    if(b[j]!=0) cnt++;
  }
   printf("%d",cnt); 
}