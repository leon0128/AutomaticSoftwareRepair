#include <stdio.h>

int main(void){
    int i, j, k;
    int A, B;
    int takahashi[3];
    int aoki[3];
    int sunuke[3];

    //get input
    scanf("%d %d", &A, &B);

    //searching
    for(i = 0; i < 2; i++){
        for(j = 0; j < 2; j++){
            for(k = 0; k < 2; k++){
                if(1 * i + 2 * j + 4 * k == A){
                    takahashi[0] = i;
                    takahashi[1] = j;
                    takahashi[2] = k;
                }
            }
        }
    }

    for(i = 0; i < 2; i++){
        for(j = 0; j < 2; j++){
            for(k = 0; k < 2; k++){
                if(1 * i + 2 * j + 4 * k == B){
                    aoki[0] = i;
                    aoki[1] = j;
                    aoki[2] = k;
                }
            }
        }
    }

    for(i = 0; i < 3; i++){
        if(takahashi[i] != 0 || aoki[i] != 0){
            sunuke[i] = 1;
        }
        else {
            sunuke[i] = 0;
        }
    }

    //output answer
    printf("%d\n", 1 * sunuke[0] +  2 * sunuke[1] + 4 * sunuke[2]);
    return 0;
}