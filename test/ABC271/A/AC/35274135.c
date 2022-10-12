#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char printx(int a){
    if(0<=a && a<=9) return '0'+a;
    else return 'A'+a-10;
}

int main(void){
    int N;
    scanf("%d", &N);

    printf("%c%c\n", printx(N/16), printx(N%16));

    return 0;
}