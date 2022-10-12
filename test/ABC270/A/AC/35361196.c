#include <stdio.h>

int main() {
    int A, B, i, N[3], result = 0;
    scanf("%d %d", &A, &B);
    for(i = 0; i < 3; i++){
        N[i] = 0;
    }
    if(A == 1){
        N[0]++;
    }
    if(B == 1){
        N[0]++;
    }
    if(A == 2){
        N[1]++;
    }
    if(B == 2){
        N[1]++;
    }
    if(A == 4){
        N[2]++;
    }
    if(B == 4){
        N[2]++;
    }
    if(A == 3){
        N[0]++;
        N[1]++;
    }
    if(B == 3){
        N[0]++;
        N[1]++;
    }
    if(A == 5){
        N[0]++;
        N[2]++;
    }
    if(B == 5){
        N[0]++;
        N[2]++;
    }
    if(A == 6){
        N[1]++;
        N[2]++;
    }
    if(B == 6){
        N[1]++;
        N[2]++;
    }
    if(A == 7){
        N[0]++;
        N[1]++;
        N[2]++;
    }
    if(B == 7){
        N[0]++;
        N[1]++;
        N[2]++;
    }
    if(N[0] == 1 || N[0] == 2){
        result += 1;
    }
    if(N[1] == 1 || N[1] == 2){
        result += 2;
    }
    if(N[2] == 1 || N[2] == 2){
        result += 4;
    }
    printf("%d", result);
    return 0;
}