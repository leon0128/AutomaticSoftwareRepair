#include<stdio.h>
int main(void){
 int n,m,t,aa,ii;
 int a[100000],x[100000],y[100000];
 scanf("%d %d %d\n",&n,&m,&t);
 for(int j=1;j<n;j++){
   scanf("%d",&a[j]);
 }
  for(int i=1;i<=m;i++){
   scanf("%d %d",&x[i],&y[i]);
   //  printf("%d%d",x[i],y[i]);
 }
  aa=t;
  ii=1;
  for(int k=1;k<n;k++){
    aa-=a[k];
     //   printf("%d%d",aa,k);
    if(aa<=0){
      printf("No");
      break;
    }
    if(k==(x[ii]-1) && ii<=m){
    	aa+=y[ii];
        ii++;
    }
    else if(aa>=0 && k==(n-1)){
      printf("Yes");
      break;
    }
  }
 return 0;
}