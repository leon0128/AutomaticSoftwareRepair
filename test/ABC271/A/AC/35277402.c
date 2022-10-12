#include <stdio.h>

void func(int n){
    if(n < 10){
            printf("%d", n);
    }
    switch(n){
        case 10:
            printf("A");
            break;
        case 11:
            printf("B");
            break;
        case 12:
            printf("C");
            break;
        case 13:
            printf("D");
            break;
        case 14:
            printf("E");
            break;
        case 15:
            printf("F");
            break;
    }
    return ;
}

int main(void){
    int N;

    scanf("%d", &N);
    func(N / 16); func(N % 16);
    printf("\n");

    return 0;
}