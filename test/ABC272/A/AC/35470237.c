#include <stdio.h>
int main(void){
    int i,n,k,sum;
    sum=0;
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%d",&k);
        sum+=k;
    }
    printf("%d",sum);
}
