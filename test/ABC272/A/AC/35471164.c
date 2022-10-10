#include <stdio.h>
int main(){
    int n, a[101], cnt=0;
    scanf("%d\n", &n);
    for(int i=0; i<n; i++){
        scanf("%d\n", &a[i]);
        cnt += a[i];
    }
    printf("%d", cnt);
    return 0;
}