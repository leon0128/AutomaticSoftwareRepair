#include <stdio.h>

int main(void){
    int x,y,n,s1,s2;
    scanf("%d%d%d",&x,&y,&n);
    if(x*3<y){ printf("%d",n*x); return 0; }
    s1=n/3;
    s2=n%3;
    y=y*s1;
    x=x*s2;
    printf("%d",x+y);
    
}
