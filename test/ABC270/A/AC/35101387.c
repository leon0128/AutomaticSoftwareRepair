#include<stdio.h>
#include<stdlib.h>

int main(){
    int a,b,c;
    int alist[3];
    int blist[3];
    int clist[3];
    int atem,btem;
    scanf("%d %d",&a,&b);
    for(int i=0;i<3;i++){
        atem=a%2;
        a=a/2;
        btem=b%2;
        b=b/2;
        alist[i]=atem;
        blist[i]=btem;
    }
    for(int i=0;i<3;i++){
        if(alist[i]==0 && blist[i]==0){
            clist[i]=0;
        }else{
            clist[i]=1;
        }
    }
    c=(clist[0])*1 + (clist[1])*2 + (clist[2])*4;
    printf("%d",c);
    return 0;
}