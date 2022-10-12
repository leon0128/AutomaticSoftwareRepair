//268-a

#include <stdio.h>

int main(void){
    int a,b,c,d,e;
    scanf("%d %d %d %d %d",&a,&b,&c,&d,&e);
    int count = 0;
    int input[5];
    int i;
    int u=0;
    input[0] = a;
    input[1] = b;
    input[2] = c;
    input[3] = d;
    input[4] = e;

    for (i=0; i<5; i++){
        if(input[i]>=0){
            for(int j=i+1; j<5; j++){
                if(input[i]==input[j]){
                    input[j]=-1;
                    //u=1;
                    
                }
            }
            count ++;
        }
    }
    printf("%d\n",count);
    return 0;
}