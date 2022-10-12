#include<stdio.h>
int X,Y,N;
int min(int a, int b){
    return (a<b)?a:b;
}

int main(){
    scanf("%d %d %d", &X, &Y, &N);
    int i, dp[101];
    dp[0]=0;
    for(i=0;i<=N;i++){
        if(i>=3)dp[i] = min(dp[i-1]+X, dp[i-3]+Y);
        else if(i>=1)dp[i] = dp[i-1]+X;
    }
    printf("%d\n", dp[N]);
    return 0;
}