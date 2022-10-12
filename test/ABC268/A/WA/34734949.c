#include<stdio.h>
int main(void){
  int i,l,ans=1;
  int a[5];
  for(i=1;i<5;i++){
    scanf("%d",&a[i]);
    for(l=0;l<i;l++){
		if(a[l]==a[i]){
			ans++;
          	break;
        }
    }
  }
  printf("%d",5-ans);
  return 0;
}