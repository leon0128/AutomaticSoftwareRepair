#include<stdio.h>

int main(void)
{
    char s[20];
    int i;
    scanf("%s", s);
    if(strcmp(s,"Monday")==0){
        i=5;
    }
    if(strcmp(s,"Tuesday")==0){
        i=4;
    }
    if(strcmp(s,"Wednesday")==0){
        i=3;
    }
    if(strcmp(s,"Thursday")==0){
        i=2;
    }
    if(strcmp(s,"Friday")==0){
        i=1;
    }
    
    printf("%d",i);
    return 0;
}