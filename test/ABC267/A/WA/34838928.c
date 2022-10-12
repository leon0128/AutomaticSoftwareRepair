#include <stdio.h>

int main (void){
    char* DayOfWeek;
    scanf("%s",DayOfWeek);

    if(DayOfWeek=="Monday"){
        printf("5");
    }
    if(DayOfWeek=="Tuesday"){
        printf("4");
    }
    if(DayOfWeek=="Wednesday"){
        printf("3");
    }
    if(DayOfWeek=="Thursday"){
        printf("2");
    }
    if(DayOfWeek=="Friday"){
        printf("1");
    }
    else{
        printf("-1");
    }
}