#include<stdio.h>
#include<string.h>

int i = 0;

int main(){
    int n, ans = 0;
    scanf("%d", &n);
    int A[n];
    for(i = 0; i < n; i++){
        scanf("%d", &A[i]);
    }

    for(i = 0; i < n; i++){
        ans += A[i];
    }
    printf("%d", ans);
    return 0;
}