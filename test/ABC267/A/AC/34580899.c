#include <stdio.h>

int main(void){
    char day[10];
    
    scanf("%s", day);
    
    if(day[0]=='M'){
        printf("5");
    }
    else if(day[0] == 'T'&&day[1]=='u'){
        printf("4");
    }
    else if(day[0] == 'W'){
        printf("3");
    }
    else if(day[0] == 'T'){
        printf("2");
    }
    else if(day[0] == 'F'){
        printf("1");
    }
}