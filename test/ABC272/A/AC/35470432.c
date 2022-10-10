#include <stdio.h>
#include <string.h>
int main(void){
    int n, a[200], ans=0;
    scanf("%d", &n);
    for(int i = 0; i<n; i++){
        scanf("%d", &a[i]);
    }
    for(int i = 0; i<n; i++){
        ans = ans + a[i];
    }
    printf("%d", ans);    
}