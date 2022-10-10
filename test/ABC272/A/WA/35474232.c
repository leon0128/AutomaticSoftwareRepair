#include <stdio.h>
int main(){
    int n,sum=0;
    int a[100];
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&a);
        sum+=a;
    }
    printf("%d\n",sum);

    return 0;
}