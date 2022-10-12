#include <stdio.h>
#include <math.h>
int main(void){
    int a, b;
    int alpha[3], beta[3], gamma[3];
    scanf("%d %d", &a, &b);
    for(int i = 0; i<3; i++){
        alpha[i] = 0;
        beta[i] = 0;
        gamma[i] = 0;
    }
    if(a%2 == 1){
        alpha[0] = 1;
    }
    if(b%2 == 1){
        beta[0] = 1;
    }
    if(alpha[0] == 1){
        if(a-1 == 2){
            alpha[1] = 1;
        }else if(a-1 == 4){
            alpha[2] = 1;
        }else if(a-1 == 6){
            alpha[1] = 1;
            alpha[2] = 1;
        }
    }else {
        if(a == 2){
            alpha[1] = 1;
        }else if(a == 4){
            alpha[2] = 1;
        }else if (a == 6){
            alpha[1] = 1;
            alpha[2] = 1;
        }
    }
    if(beta[0] == 1){
        if(b-1 == 2){
            beta[1] = 1;
        }else if(b-1 == 4){
            beta[2] = 1;
        }else if(b-1 == 6){
            beta[1] = 1;
            beta[2] = 1;
        }
    }else {
        if(b == 2){
            beta[1] = 1;
        }else if(b == 4){
            beta[2] = 1;
        }else if(b == 6){
            beta[1] = 1;
            beta[2] = 1;
        }
    }
    for(int i = 0; i<3; i++){
        if(alpha[i] + beta[i] > 0)
        gamma[i] = 1;
    }
    printf("%d", gamma[0] + gamma[1]*2 + gamma[2]*4);
}