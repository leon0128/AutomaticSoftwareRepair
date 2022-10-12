#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(void){
    int a, b, c, d, e, i, count= 0;
    int n[105] = {0};

    scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);

    n[a]++;
    n[b]++;
    n[c]++;
    n[d]++;
    n[e]++;

    for(i = 0; i < 101; i++){
        if(n[i]){
            count++;
        }
    }

    printf("%d", count);

    return 0;
}