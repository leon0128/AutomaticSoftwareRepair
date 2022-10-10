#include <stdio.h>
int main(){
    int n,i,a,s;
    scanf("%d",&n);
    for(i = 0;i < n;++i){
        scanf("%d",&a);
        s = s + a;
    }
    printf("%d",s - 16);
    return 0;
}