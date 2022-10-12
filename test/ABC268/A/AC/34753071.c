#include<stdio.h>

int main(void){
  int a[5];
  
	for(int i=0;i<5;i++)
		scanf("%d",&a[i]);
	
	for(int m=4;m>=0;m--){ 
		for(int j=0;j<m;j++){ 
			if(a[j]>a[j+1]){
				int w;
				w=a[j];
				a[j]=a[j+1];
				a[j+1]=w;
			}
		}
	}
  
   int x=1;
   int f=a[0];
   for(int k=0;k<5;k++){
     if(a[k]!=f){
       x++;
       f=a[k];
     }
   }

  printf("%d",x);
  
  return 0;
}