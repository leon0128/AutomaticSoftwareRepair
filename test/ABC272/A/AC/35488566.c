#include <stdio.h>
int main(){
    int n,i,a,s = 0;
    scanf("%d",&n);
    for(i = 0;i < n;++i){
        scanf("%d",&a);
        s = s + a;
    
    }
    printf("%d\n",s);
    return 0;
}