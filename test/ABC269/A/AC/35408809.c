#include<stdio.h>
int main(){
    int a[4],i;
    for(i=0;i<5;i++)scanf("%d",&a[i]);
    printf("%d\nTakahashi",(a[0]+a[1])*(a[2]-a[3]));
    return 0;
}