#include <stdio.h>

int main(void){
    int N , get;
    int ans = 0;

    scanf("%d", &N);

    for(int i = 0; i < N; i++){
        scanf("%d", &get);
        ans = ans + get;
    }
    printf("%d", ans);
}