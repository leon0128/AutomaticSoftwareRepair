#include<stdio.h>

int main (int argc, char const argv[]){
    int x,y,n;
    scanf("%d%d%d",&x,&y,&n);
    int three = 0;
    three = n/3;
    n-=(three)*3;
    printf("%d",three*y+n*x);
    return 0;
}

