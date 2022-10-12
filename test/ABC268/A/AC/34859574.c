#include <stdio.h>
int main(void){
    int A[5], B[5];
    for(int i=0; i<5; i++){
        scanf("%d", &A[i]);
    }
    
    int cnt=0,j=0;
    for(int i=0; i<5; i++){
        if(i==0){
            B[j]=A[i];
            j++;
        }else{
            int k=0;
           for(k=0; k<j; k++){
               if(A[i]==B[k]){
                   cnt++;
                   break;
                }
           }
            if(A[i]!=B[k]){
             B[j]=A[i];
                j++;
            }
        }
    }
    printf("%d\n", 5-cnt);
}