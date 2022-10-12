#include <stdio.h>
#include <string.h>

int main(void) {
    int count[101],sum=0;
    int i,j,k;
    int a,b,c,d,e;

    scanf("%d %d %d %d %d",&a,&b,&c,&d,&e);
    
    for(i=0;i<101;i++){
        count[i]=0;
        //printf("%d ",count[i]);
    }
    
    for(i=0;i<101;i++){
        if(i==a) count[i]++;
        else if(i==b) count[i]++;
        else if(i==c) count[i]++;
        else if(i==d) count[i]++;
        else if(i==e) count[i]++;
    }

    for(i=0;i<101;i++){
        if(count[i]!=0) count[i]=1;
        sum += count[i];
    }
    printf("%d\n",sum);
    
}   

