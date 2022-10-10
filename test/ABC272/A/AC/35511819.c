#include <stdio.h>

int main() {
    int N;
    int sum = 0;
    

    scanf("%d",&N);
    
    int num[N];
    for(int i = 0; i < N; i++){
        scanf("%d",&num[i]);
    }

    for(int i = 0; i <N; i++){
        sum += num[i];
    }
    printf("%d",sum);
    return 0;
}