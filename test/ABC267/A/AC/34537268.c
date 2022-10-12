//267-a

#include <stdio.h>
#include <string.h>

int main(void){
    char s[20];
    scanf("%s",s);
    if(strcmp(s,"Monday")==0){
        printf("5\n");
        return 0;
    } else if(strcmp(s,"Tuesday")==0){
        printf("4\n");
        return 0;
    } else if(strcmp(s,"Wednesday")==0){
        printf("3\n");
        return 0;
    } else if(strcmp(s,"Thursday")==0){
        printf("2\n");
        return 0;
    } else {
        printf("1\n");
        return 0;
    }

    return 0;
}