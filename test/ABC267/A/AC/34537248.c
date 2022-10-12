#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(void){
    char s[30];

    scanf("%s", s);

    if(!strcmp(s, "Monday")){
printf("5");
    }
    else if(!strcmp(s, "Tuesday")){
printf("4");
    }
    else if(!strcmp(s, "Wednesday")){
printf("3");
    }
    else if(!strcmp(s, "Thursday")){
        printf("2");
    }
    else{
        printf("1");
    }



    return 0;
}