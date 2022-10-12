#include<stdio.h>
#include<stdlib.h>
int main(){

    char s[20];
    
    scanf("%s",s);
    (void)getchar();

    if(s[0]=='M'){
        printf("5\n");
    }
    
    if(s[0]=='T' && s[1]=='u'){
        printf("4\n");
    }
    
    if(s[0]=='W'){
        printf("3\n");
    }

    if(s[0]=='T' && s[1]=='h'){
        printf("2\n");
    }

    if(s[0]=='F'){
        printf("1\n");
    }

    return 0;
}