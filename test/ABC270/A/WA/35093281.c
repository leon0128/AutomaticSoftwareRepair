#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(void){
    int a, b;

    scanf("%d %d", &a, &b);

    if(a == 1 && b == 1){
        printf("1");
        return 0;
    }

    if(a == 1 && b == 2){
        printf("1");
        return 0;
    }

    if(a == 1 && b == 4){
        printf("1");
        return 0;
    }

    if(a == 2 && b == 1){
        printf("1");
        return 0;
    }

    if(a == 2 && b == 2){
        printf("2");
        return 0;
    }

    if(a == 2 && b == 4){
        printf("2");
        return 0;
    }

    if(a == 4 && b == 1){
        printf("1");
        return 0;
    }

    if(a == 4 && b == 2){
        printf("2");
        return 0;
    }

    if(a == 4 && b == 4){
        printf("4");
        return 0;
    }

    if(a == 0 && b == 0){
        printf("0");
        return 0;
    }

    return 0;
}