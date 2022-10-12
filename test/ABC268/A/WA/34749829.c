#include <stdio.h>
int main(void){
    int integer[5];
    int cnt=0;
    int kari;
    
    for(int i = 0; i<5; i++){
    scanf("%d", &(integer[i]));
    }
    
    for(int i = 1; i<5; i++){
        for(int j = 0; j<5; j++){
            if(integer[i]<integer[j]){
                kari = integer[i];
                integer[i] = integer[j];
                integer[j] = kari;
            }    
        }
    }
    
    for(int i = 0; i<5; i++){
        if(integer[i]!=0 && integer[i]!=integer[i+1]){
        cnt++;
        }
    }
   
    printf("%d", cnt);
    
}
