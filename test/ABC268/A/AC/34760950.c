#include<stdio.h>
int main(){
int ar[5];
int br[110]={0};
int cnt=0;

for(int i=0;i<5;i++){
scanf("%d",&ar[i]);
br[ar[i]]++;
}

for(int i=0;i<110;i++){
if(br[i]!=0){
cnt++;}
}
printf("%d",cnt);
}


