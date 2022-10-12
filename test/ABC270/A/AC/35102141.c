#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(void){
    int a, b, i;
    int n[3] = {0}, m[3] = {0};
    int sum = 0;

    scanf("%d %d", &a, &b);

    if(a == b){
        printf("%d", a);
        return 0;
    }

   if(a == 1 || a == 3 || a == 5 || a == 7){
    n[0] = 1;
   }

    if(a == 2 || a == 3 || a == 6 || a == 7){
    n[1] = 1;
   }

   
    if(a == 4 || a == 5 || a == 6 || a == 7){
    n[2] = 1;
   }

   if(b == 1 || b == 3 || b == 5 || b == 7){
    m[0] = 1;
   }

    if(b == 2 || b == 3 || b == 6 || b == 7){
    m[1] = 1;
   }

   
    if(b == 4 || b == 5 || b == 6 || b == 7){
    m[2] = 1;
   }

   for(i = 0; i < 3; i++){
    if(n[i] == 1 || m[i] == 1){
        if(i == 0){
            sum += 1;
        }

        if(i == 1){
            sum += 2;
        }

        if(i == 2){
            sum += 4;
        }

    }
   }

   printf("%d", sum);

    

    return 0;
}