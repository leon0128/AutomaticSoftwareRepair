#include<stdio.h>
int main(){
    char s[10];
    scanf("%s",&s);
    if(s[0]=='M'){
        printf("5");
    }else if(s[0]=='T'){
        if(s[1]=='u'){
            printf("4");
        }else{
            printf("2");
        }
    }else if(s[0]=='W'){
        printf("3");
    }else{
        printf("1");
    }
    return 0;
}