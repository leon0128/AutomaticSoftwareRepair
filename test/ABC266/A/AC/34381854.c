#include <stdio.h>
#include <string.h>

int main(void){
    char str[100];
    do{
    scanf("%s",str);
    }while(strlen(str)%2==0);
    
    printf("%c",str[strlen(str)/2 ]);
    
    return 0;
    
}