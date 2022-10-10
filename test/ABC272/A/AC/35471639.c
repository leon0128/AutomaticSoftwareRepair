#include <stdio.h>
int main(void){
    // Your code here!
    int N;
    scanf("%d",&N);
    
    int a;
     int sum=0;
    for(int i=0; i<N; i++){
        scanf("%d", &a);
        sum+=a;
    }

    printf("%d\n",sum);
}
