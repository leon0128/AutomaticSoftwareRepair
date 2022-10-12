#include <stdio.h>
int main(void){
    int index[5],cou=0,sum=0,i,z,dummy;
    for(i=0;i<=4;i++){
        scanf("%d",&index[i]);
    }
    dummy=index[0];
    for(i=0;i<=3;i++){
        for(z=i;z<=4;z++){
            if(index[i]<index[z]){
                dummy=index[i];
                index[i]=index[z];
                index[z]=dummy;
            }
        }
    }
    for(i=0;i<=3;i++){
        i=i+cou;
        cou=0;
        for(z=1+i;z<=4;z++){
            if(index[i]==index[z]){
                cou++;
            }
        }
        sum=sum+cou;
    }
    
    printf("%d",5-sum);
    return 0;
}