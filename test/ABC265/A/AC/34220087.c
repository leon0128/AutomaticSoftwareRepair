#include <stdio.h>
int main(void){
    int X;
    scanf("%d",&X);
    int Y;
    scanf("%d",&Y);
    int N;
    scanf("%d",&N);
    
    int count=0;
    if(3*X>Y){
        for(int i=0;i<=(N/3)-1;i++){
        count++;
    }
    }
    
    int count1=0;
    for(int i=0;i<=N-3*count-1;i++){
        count1++;
    }
    int sum;
    sum=count*Y+count1*X;
    printf("%d",sum);
    return 0;
}
