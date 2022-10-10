#include<stdio.h>
#include<stdlib.h>


int main(void){
    int i;
    int n;
    int tmp,error;
    int sum = 0;

    error = scanf("%d",&n);
    if(error != 1){
        printf("load error\n");
        exit(1);
    }
    for(i = 0; i < n; i++){
        error = scanf("%d",&tmp);
        if(error != 1){
            printf("load error\n");
            exit(1);
        }
        sum += tmp;
    }

    printf("%d\n",sum);

    return 0;
}