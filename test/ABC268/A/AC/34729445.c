#include <stdio.h>
 int a[103],i,result,sum,k;
int main(void){
    result=0;
    for (i=0;i<5;i++){
        scanf("%d",&k);
        a[k]++;
        if(a[k]==1){
            result++;
        }
    }
    printf("%d",result);
}
