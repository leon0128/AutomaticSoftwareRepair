#include <stdio.h>

int main(void){
    int n;
    scanf("%d",&n);
    if( (!(n%4) && n%100) || !(n%400)){
        printf("YES");
    }else{
        printf("NO");
    }
    return 0;
}
