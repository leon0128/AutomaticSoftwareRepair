#include<stdio.h>
int main(){
    int a,b,c=0,s[3];
    scanf("%d %d",&a,&b);
    if(a%2==1 || b%2==1){
        s[0]=1;
        c=c+1;
    }
    if(a==2 || b==2 || a==3 || a==6 || a==7 || b==3 || b== 6 || b==7){
        s[1]=1;
        c=c+2;
    }
    if(a>3 || b>3){
        s[2]=1;
        c=c+4;
    }
    printf("%d",c);
    return 0;
}