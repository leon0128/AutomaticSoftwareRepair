#include <stdio.h>
#include <string.h>

int main (void){
    char DayOfWeek[10];
    scanf("%s",DayOfWeek);

    if(strcmp(DayOfWeek,"Monday")==0){
        printf("5");
    }
    if(strcmp(DayOfWeek,"Tuesday")==0){
        printf("4");
    }
    if(strcmp(DayOfWeek,"Wednesday")==0){
        printf("3");
    }
    if(strcmp(DayOfWeek,"Thurshday")==0){
        printf("2");
    }
    if(strcmp(DayOfWeek,"Friday")==0){
        printf("1");
    }
}