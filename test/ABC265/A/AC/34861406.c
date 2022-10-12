#include <stdio.h>
int main(void){
    int x,y,n,ans=10000000,sum;
    scanf("%d %d %d",&x,&y,&n);
    for(int i=0;i<=n;i++){
          for(int t=0;t<=n-i;t++){
                if(i+3*t==n){
                    sum=0;
                    sum=i*x+t*y;
                    if(sum<ans){
                          ans=sum;
                    }
                }
          }
    }
    printf("%d\n",ans);
    return 0;
    
}