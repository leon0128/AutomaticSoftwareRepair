#include <stdio.h>
int main(void){
    int num;
    int result=0;
    scanf("%d", &num);
    
    if(num%4==0)result=1;
    if(num%100==0)result=0;
    if(num%400==0)result=1;
    
    if(result==1)printf("YES\n");
    else printf("NO\n");
    
    return 0;
}