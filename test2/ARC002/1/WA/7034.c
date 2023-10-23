#include <stdio.h>

int main(void){
        char input[4];
        int year;
        if(fgets(input, 4, stdin))
        sscanf(input, "%d", &year);
        if(year%4 == 0 || year%100 != 0 || year%400 == 0){
                if(year%4 == 0){
                        printf("YES\n");
                }
                else if(year%100 != 0){
                        printf("NO\n");
                }
                else if(year%400 == 0){
                        printf("YES\n");
                }
        }
        else{
                printf("NO\n");
        }

        return 0;
}