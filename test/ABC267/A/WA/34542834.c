#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(void){
    char s[64];
    scanf("%s",&s);
    if(s == "Monday"){
        printf("5");
    }else if(s == "Tuesday"){
        printf("4");
    }else if(s == "Wednesday"){
        printf("3");
    }else if(s == "Thursday"){
        printf("2");
    }else if(s == "Friday"){
        printf("1");
    }
    return 0;
}