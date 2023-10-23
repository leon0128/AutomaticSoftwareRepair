#include <stdio.h>
int main(void){
    // Your code here!
    int Y;
    scanf("%d",&Y);
    
    if(Y%4==0 && (!(Y%100==0) || Y%400==0)){
        printf("YES\n");
    }
    else{
        printf("NO");
    }
    
    return 0;
}
