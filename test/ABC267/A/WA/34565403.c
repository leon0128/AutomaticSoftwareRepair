#include<stdio.h>

int main(void){
    char S;
    scanf("%c",&S);
    if(S=="Monday"){
        printf("5");
    }
    else if(S=="Tuesday"){
        printf("4");
    }
    else if(S=="Wednesday"){
        printf("3");
    }
    else if(S=="Thursday"){
        printf("2");
    }
    else{
        printf("1");
    }
    return 0;
}