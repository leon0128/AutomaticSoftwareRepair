#include<stdio.h>
int main(void){
    char a[10];
    int b=0;
    scanf("%s",a);
    if(a[1]=='o'){
        b=0;
    }else if(a[1]=='u'){
        b=1;
    }else if(a[1]=='e'){
        b=2;
    }else if(a[1]=='h'){
        b=3;
    }else if(a[1]=='r'){
        b=4;
    }
    printf("%d",5-b);
    return 0;
}