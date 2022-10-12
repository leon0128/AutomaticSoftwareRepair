
#include <stdio.h>

int main(void){
    int x,y,n;
    scanf("%d %d %d",&x,&y,&n);

    if (y<3*x){
        int threeApple=n/3;
        int oneApple=n%3;
        printf("%d",(x*oneApple)+(y*threeApple));
    }
    else{
        printf("%d",x*n);
    }
}
