#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    int A[200],B,i;
    for(i=0; i<200; i++) A[i]=0;
    for(i=0; i<5; i++){
        scanf("%d",&B);
        A[B]++;
    }
    int ans=0;
    for(i=0; i<=100; i++) ans+=(A[i]>0);

    printf("%d\n",ans);

    return 0;
}