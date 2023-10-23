#include<stdio.h>

int main(void){

    int Y;
    scanf("%d",&Y);

    // 4で割り切れるのであれば
    if(Y%4==0){
        // 100で割り切れないならYES
        if(Y%100!=0){
            printf("YES\n");
        // 100で割り切れるのなら
        }else{
            // 400で割り切れるのならYES
            if(Y%400==0){
                printf("YES\n");
            // 400で割り切れないのならNO
            }else{
                printf("NO\n");
            }
        }
    // それ以外ならNO
    }else{
        printf("NO\n");
    }

    return 0;
}