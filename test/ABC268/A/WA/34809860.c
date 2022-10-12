#include<stdio.h>
int main(void){
    int a[5];
    for(int x=0;x<5;x++){
        scanf("%d",&a[x]);
    }
    int b=1;
  	for(int y=1;y<5;y++){
      for(int z=0;z<y;z++){
        if(a[y]==a[z]){
          b++;
        }
      }
    }
    printf("%d",b);
    return 0;
}