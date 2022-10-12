#include <stdio.h>

int main() {
       int a = 0;
       scanf("%d", &a);
       
       if(a >  15){
             printf("%x\n", &a);
        }
        else if(a  > 0){
              printf("0%x\n",&a);
         }else printf("00\n");
       return 0;
}