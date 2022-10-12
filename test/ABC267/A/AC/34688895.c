#include <stdio.h>
#include <string.h>

int main(void){
    char S[100];
    scanf("%s",S);

    if(!strcmp(S,"Monday")){
        printf("5\n");
    }else if(!strcmp(S,"Tuesday")){
        printf("4\n");
    }else if(!strcmp(S,"Wednesday")){
        printf("3\n");
    }else if(!strcmp(S,"Thursday")){
        printf("2\n");
    }else if(!strcmp(S,"Friday")){
        printf("1\n");
    }
return 0;
}