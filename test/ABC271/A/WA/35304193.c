#include<stdio.h>
int main(void){
    int N;
    char a,b;
    scanf("%d",&N);
    a=(int)N/16;
    b=N%16;
    if(N<16){
        a='0';
    }
    if(a==10){
        a='A';
    }else if(a==11){
        a='B';
    }else if(a==12){
        a='C';
    }else if(a==13){
        a='D';
    }else if(a==14){
        a='E';
    }else if(a==15){
        a='F';
    }
    if(b==10){
        b='A';
    }else if(b==11){
        b='B';
    }else if(b==12){
        b='C';
    }else if(b==13){
        b='D';
    }else if(b==14){
        b='E';
    }else if(b==15){
        b='F';
    }

    printf("%c%c",a,b);
    return 0;
}