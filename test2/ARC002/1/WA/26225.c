//AtCoder002-A
#include<stdio.h>

int main(void)
{
	int Y;
	
	scanf("%d",&Y);
    
    if(Y%4==0){ 
        if(Y%100==0){
            if(Y%400==0){
                printf("YES\n");
            }
            else{
                printf("NO\n");
            }
        }
        else if(Y%100!=0){
            if(Y%400==0){
                printf("YES\n");
            }
            else{
                printf("NO\n");
            }
        }
    }
    
    else if(Y%4!=0){
        if(Y%100==0){
            if(Y%400==0){
                printf("YES\n");
            }
            else if(Y%400!=0){
                printf("NO\n");
            }
        }
        else if(Y%100!=0){
            if(Y%400==0){
                printf("YES\n");
            }
            else if(Y%400!=0){
                printf("NO\n");
            }
        }
    }
	return (0);
}
