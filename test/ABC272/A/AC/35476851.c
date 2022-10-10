#include <stdio.h>
int main(){
    int N,A,Sum;
    scanf("%d",&N);
    int i;
    for(i=0,Sum=0;i<N;i++){
        scanf("%d",&A);
        Sum += A;
    }
    printf("%d\n",Sum);
    return 0;
}