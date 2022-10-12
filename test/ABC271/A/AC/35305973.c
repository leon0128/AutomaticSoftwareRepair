#include <stdio.h>

int main() {
       int a = 0;
       scanf("%d", &a);
       
       if(a >  15){
             printf("%X\n", a);
        }
        else if(a  > 0){
              printf("0%X\n",a);
         }else printf("00\n");
       return 0;
}