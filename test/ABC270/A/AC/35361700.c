#include<stdio.h>
#include<math.h>
#include <stdlib.h>
int main(){
    int score[2][3]={1,2,4,0,0,0};
    int A;
    int B;
    int result=0;
    scanf("%d %d",&A,&B);
    if(A==0);
    if(A==1){
        score[1][0]++;
    }
    if(A==2){
        score[1][1]++;
    }
    if(A==4){
        score[1][2]++;
    }
    if(A==3){
        score[1][0]++;
        score[1][1]++;
    }
    if(A==5){
        score[1][0]++;
        score[1][2]++;
    }
    if(A==6){
        score[1][1]++;
        score[1][2]++;
    }
    if(A==7){
        score[1][0]++;
        score[1][1]++;
        score[1][2]++;
    }
    if(B==0);
    if(B==1){
        score[1][0]++;
    }
    if(B==2){
        score[1][1]++;
    }
    if(B==4){
        score[1][2]++;
    }
    if(B==3){
        score[1][0]++;
        score[1][1]++;
    }
    if(B==5){
        score[1][0]++;
        score[1][2]++;
    }
    if(B==6){
        score[1][1]++;
        score[1][2]++;
    }
    if(B==7){
        score[1][0]++;
        score[1][1]++;
        score[1][2]++;
    }
    int i;
    for(i=0;i<3;i++){
        if(score[1][i]!=0) {
            result += score[0][i];
        }
    }
    printf("%d\n",result);
    return 0;
}
