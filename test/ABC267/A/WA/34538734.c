#include<stdio.h>
#define Monday 1
#define Tuesday 2
#define Wednesday 3 
#define Thursday 4
#define Friday 5

int main(){
    int S;
    int ans;
    scanf("%s", S);
    if(S=1){
        ans = 5;
    }else if(S = 2){
        ans = 4;
    }else if(S = 3){
        ans = 3;
    }else if(S = 4){
        ans = 2;
    }else if(S = 5){
        ans = 1;
    }
    printf("%d", ans);

    return 0;
}