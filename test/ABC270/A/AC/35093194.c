#include <stdio.h>
int main(){
    int A,B;
    scanf("%d %d",&A,&B);
    int C = 0;
    if((A%2==1)||(B%2==1)){
        C += 1;
    }
    A /= 2;
    B /= 2;
    if((A%2==1)||(B%2==1)){
        C += 2;
    }
    A /= 2;
    B /= 2;
    if((A%2==1)||(B%2==1)){
        C += 4;
    }
    printf("%d\n",C);
    return 0;
}