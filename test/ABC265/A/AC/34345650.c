#include<stdio.h>
int main(void){
    int x,y,n,ama,syou;
    scanf("%d %d %d",&x ,&y ,&n);
    if(x<y/3){
        y=x*3;
    }
    syou=n/3;
    ama=n%3;
    syou=syou*y;
    ama=ama*x;
    syou=syou+ama;
    printf("%d",syou);
    return 0;
}