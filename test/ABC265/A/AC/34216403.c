#include<stdio.h>
int main(){
    int x,y,n;
    scanf("%d %d %d",&x,&y,&n);
    if(n<3){
        printf("%d\n",x*n);
    }
    else{
        if(y/x>=3){
            printf("%d\n",x*n);
        }
        else if(y/x<3){
            int m=n/3;
            int m2=n%3;
            printf("%d\n",(x*m2)+(y*m));
        }
    }
    return 0;
}