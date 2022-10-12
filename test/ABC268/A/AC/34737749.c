#include<stdio.h>
#include<stdlib.h>
int main(void){
    int i,j,a[5],cnt=0,tmp;
    for(i=0;i<5;i++){
        scanf("%d",&a[i]);
    }
    for(i=0;i<5;i++){
        for(j=0;j<5;j++){
            if(a[j]<a[j+1]){
                tmp=a[j];
                a[j]=a[j+1];
                a[j+1]=tmp;
            }
        }
    }
    for(i=0;i<5;i++){
        if(a[i]==a[i+1]){
            cnt++;
        }
    }
    printf("%d",5-cnt);
}