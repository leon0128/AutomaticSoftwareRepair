//268-a

#include <stdio.h>

int main(void){
    int a,b,c,d,e;
    scanf("%d %d %d %d %d",&a,&b,&c,&d,&e);
    int count = 0;
    int input[5];
    int i;
    input[0] = a;
    input[1] = b;
    input[2] = c;
    input[3] = d;
    input[4] = e;

    for(i=0; i<5; i++){
        if(a!=input[i]){
            count++;
        }
    }
    printf("%d",count);
    return 0;
}