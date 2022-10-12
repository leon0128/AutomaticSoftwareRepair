#include<stdio.h>

int main(){
    char s[10];scanf("%s",s);
    if(s[0]=='M'){
        printf("%d",5);
    } else if(s[0]=='T'&&s[1]=='u'){
        printf("%d",4);
    } else if(s[0]=='W'){
        printf("%d",3);
    } else if(s[0]=='T'&&s[1]=='h'){
        printf("%d",2);
    } else if(s[0]=='F'){
        printf("%d",1);
    }
    return 0;
}