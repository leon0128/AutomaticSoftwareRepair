#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(){
    int t;
    scanf("%d", &t);
    t = 1;
    char s[100];
    while(t--){
        scanf("%s", s);
        if(strcmp(s, "Monday") == 0){
            printf("5");
        }else if(strcmp(s, "Tuesday") == 0){
            printf("4");
        }else if(strcmp(s, "Wednesday") == 0){
            printf("3");
        }else if(strcmp(s, "Thursday") == 0){
            printf("2");
        }else{
            printf("1");
        }
        
    
    }
    return 0;
}