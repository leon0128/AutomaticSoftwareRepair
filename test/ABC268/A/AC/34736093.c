#include <stdio.h>

int main(void){
    int N[6];
    int counter = 0;

    for(int i = 0; i < 5; i++){
        scanf("%d", &N[i]);
        if(i == 0){
            counter++;
            continue;
        }
        int a = 0;
        for(int j = 0; j < i; j++){
            if(N[i] == N[j]) a = 1;
        }
        if(a == 0) counter++;
    }

    printf("%d\n", counter);
    return 0;
}