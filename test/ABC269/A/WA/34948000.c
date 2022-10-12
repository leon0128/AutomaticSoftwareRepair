#include <stdio.h>
 
int main(void){
    int a,b,c,d,ans;
    scanf("%d%d%d%d",&a,&b,&c,&d);
    ans=(a+b)*(c-d);
    if(ans>=0){
        printf("%2.d\n",(a+b)*(c-d));
    }else{
        printf("%2.d\n",-1*(a+b)*(c-d));
    }
    printf("Takahashi\n");
    return 0;
}