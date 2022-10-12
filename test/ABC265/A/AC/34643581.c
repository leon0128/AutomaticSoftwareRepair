#include<stdio.h>
int main(){
    int n,x,y;
    scanf("%d %d %d",&x,&y,&n);
    if((3*x)>y){
        printf("%d",(y*(n/3))+(x*(n%3)));
    }
    else{
        printf("%d",(x*n));
    }
    return 0;
}