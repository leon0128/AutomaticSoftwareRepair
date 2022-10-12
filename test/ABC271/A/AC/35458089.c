//ABC A
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char function(int x);

int main(void){
    int number;
    int temp_1;
    int temp_2;
    char sub;
    scanf("%d", &number);

    temp_1 = number / 16;
    if(0 <= temp_1 && temp_1 <= 9){
        printf("%d", temp_1);
    }else{
        sub = function(temp_1);
        printf("%c", sub);
    }

    temp_2 = number % 16;
    if(0 <= temp_2 && temp_2 <= 9){
        printf("%d", temp_2);
    }else{
        sub = function(temp_2);
        printf("%c", sub);
    }
    printf("\n");
    return 0;
}

char function(int n){
    if(n == 10){
        return 'A';
    }else if(n == 11){
        return 'B';
    }else if(n == 12){
        return 'C';
    }else if(n == 13){
        return 'D';
    }else if(n == 14){
        return 'E';
    }else if(n == 15){
        return 'F';
    }
}