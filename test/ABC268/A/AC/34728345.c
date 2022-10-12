#include <stdio.h>
int main(){
    int i,N,cnt,flg[110]={0};
    for(i=0,cnt=0;i<5;i++){
        scanf("%d",&N);
        if(flg[N]==0){
            cnt++;
            flg[N]=1;
        }
    }
    printf("%d\n",cnt);
    return 0;
}