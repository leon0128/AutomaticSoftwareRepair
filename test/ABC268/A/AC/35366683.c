#include<stdio.h>
int main(){
    int a[5],i,j,r=5;
    for(i=0;i<5;i++)scanf("%d",&a[i]);
    for(i=0;i<5;i++){
        for(j=i+1;j<5;j++){
            if(a[i]==a[j]){
                r--;
                break;
            }
        }
    }
    printf("%d",r);
    return 0;
}