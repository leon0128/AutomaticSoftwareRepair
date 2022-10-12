#include <stdio.h>
#include <string.h>
int main(void){
    char a[10];
    char b[10][10]={"Monday","Tuesday","Wednesday","Thursday","Friday"};
    scanf("%s",a);
    if(strcmp(a,b[0])==0){
        printf("5");
    }else if(strcmp(a,b[1])==0){
        printf("4");
    }else if(strcmp(a,b[2])==0){
        printf("3");
    }else if(strcmp(a,b[3])==0){
        printf("2");
    }else if(strcmp(a,b[4])==0){
        printf("1");
    }else{
        return 0;
    }
}
