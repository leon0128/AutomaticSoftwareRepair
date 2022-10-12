#include <stdio.h>
int main(void){
    int n;
    scanf("%d",&n);
    int t;
    if(n>=16){
        if(n/16>=10){
            t=(int)n/16;
            switch(t){
                case 10:
                printf("A");
                break;
                case 11:
                printf("B");
                break;
                case 12:
                printf("C");
                break;
                case 13:
                printf("D");
                break;  
                case 14:
                printf("E");
                break;  
                case 15:
                printf("F");
                break;                
            }
        }else{
            t=(int)n/16;
            printf("%d",t);
        }
    }else{
        printf("0");
    }
    t=(int)n%16;
            if(t>=10){
            switch(t){
                case 10:
                printf("A");
                break;
                case 11:
                printf("B");
                break;
                case 12:
                printf("C");
                break;
                case 13:
                printf("D");
                break;  
                case 14:
                printf("E");
                break;  
                case 15:
                printf("F");
                break;                
            }
        }else{
            printf("%d",t);
        }
    
   return 0; 
    
}