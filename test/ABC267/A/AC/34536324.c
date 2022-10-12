#include <stdio.h>
int main(void){
    // Your code here!
    char str[10];
    // int num2;
    
    scanf("%s", str);
    if (str[0] == 'M')
        printf("5");
    if (str[0] == 'W')
        printf("3");
    if (str[0] == 'F')
        printf("1");
    if (str[0] == 'T' && str[1] == 'u')
        printf("4");
     if (str[0] == 'T' && str[1] == 'h')
        printf("2");
    
    
    // printf("%d%d", num, num2);
    
}