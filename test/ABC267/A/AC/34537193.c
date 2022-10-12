#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(void){
    char s[100];
    scanf("%s", s);
    if(s[0] == 'T'){
        if(s[1] == 'u'){
            printf("4");
        }else {
            printf("2");
        }
    }else if(s[0] == 'M'){
        printf("5");
    }else if(s[0] == 'W'){
        printf("3");
    }else {
        printf("1");
    }
}