#include <stdio.h>

int main(void){
    int N, a;
    int sco = 0;
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d", &a);
        sco += a;
    }
    printf("%d\n", sco);
    return 0;
}