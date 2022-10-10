#include <stdio.h>
int main(void){
    int N;
    int A;
    int sum=0;
    
    scanf("%d",&N);
    for(int i=0;i<N;i++){
        scanf("%d",&A);
        sum = sum + A;
    }
   
    printf("%d",sum);

}