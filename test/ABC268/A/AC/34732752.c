#include<stdio.h>
int main(){
    int a[5],i,j,k,ans=1;
    scanf("%d %d %d %d %d",&a[0],&a[1],&a[2],&a[3],&a[4]);
    for(i=0;i<5;i++){
        for(j=0;j<4;j++){
            if(a[j]>a[j+1]){
                k=a[j+1];
                a[j+1]=a[j];
                a[j]=k;
            }
        }
    }
    for(i=0;i<4;i++){
        if(a[i]!=a[i+1]){
            ans++;
        }
    }
    printf("%d",ans);
    return 0;
}