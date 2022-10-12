#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(){
    char S[10],set[5][10] = {"Friday","Thursday","Wednesday","Tuesday","Monday"};
    scanf("%s",S);
    int i;
    for(i=0;i<5;i++){
        if(strcmp(S,set[i])==0){
            printf("%d\n",i+1);
        }
    }
    return 0;
}