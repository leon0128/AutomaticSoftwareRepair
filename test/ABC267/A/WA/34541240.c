#include<stdio.h>

int main(){
    char S[10];
    int ans;
    scanf("%s", S);
    if(S=="Monday"){
        ans = 5;
    }else if(S == "Tuesday"){
        ans = 4;
    }else if(S == "Wednesday"){
        ans = 3;
    }else if(S == "Thursday"){
        ans = 2;
    }else if(S == "Friday"){
        ans = 1;
    }
    printf("%d", ans);

    return 0;
}