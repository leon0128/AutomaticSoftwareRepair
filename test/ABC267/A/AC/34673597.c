#include <stdio.h>
#include <string.h>
int main(){
    char S[10];
    scanf("%s",S);
    if(strcmp(S,"Monday")==0){
        printf("5\n");
    }else if(strcmp(S,"Tuesday")==0){
        printf("4\n");
    }else if(strcmp(S,"Wednesday")==0){
        printf("3\n");
    }else if(strcmp(S,"Thursday")==0){
        printf("2\n");
    }else if(strcmp(S,"Friday")==0){
        printf("1\n");
    }
  
  
    return 0;
}
      