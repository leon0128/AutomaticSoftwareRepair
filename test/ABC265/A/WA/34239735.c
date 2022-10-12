#include<stdio.h>
int main(void){
 int n,m,t,aa;
 int a[100000],x[100000],y[100000];
 scanf("%d%d%d",&n,&m,&t);
  for(int i=1;i<n;i++){
  	scanf("%d",&a[i]);
    scanf("%d%d",&x[i],&y[i]);
  }
  for(int k=1;k<n;k++){
    if(k==x[k]){
    	aa=t-a[k]+y[k];
    }
    else
       aa=t-a[k];
    if(aa<=0 && k!=n-1){
      printf("No");
      break;
    }
    else if(aa>=0 && k==n-1){
      printf("Yes");
    }
  }
 return 0;
}