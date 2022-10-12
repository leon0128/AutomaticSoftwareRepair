#include<stdio.h>

int main(){
    int a,b,c,d,e;scanf("%d%d%d%d%d",&a,&b,&c,&d,&e);
    int cnt[101]={0};
    cnt[a]=cnt[b]=cnt[d]=cnt[e]=cnt[c]=1;
    int i,sum=0;
    for(i=1;i<=100;i++){
        sum+=cnt[i];
    }
    printf("%d",sum);
    return 0;
}