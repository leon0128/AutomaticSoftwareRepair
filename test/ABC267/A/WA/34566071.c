#include<stdio.h>

int main(void){
    char S;
    scanf("%c",&S);
    if(S=="Monday"){
        printf("5\n");
    }
    else if(S=="Tuesday"){
        printf("4\n");
    }
    else if(S=="Wednesday"){
        printf("3\n");
    }
    else if(S=="Thursday"){
        printf("2\n");
    }
    else{
        printf("1\n");
    }
    return 0;
}