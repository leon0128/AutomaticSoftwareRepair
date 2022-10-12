#include <stdio.h>
#include <string.h>

int main(void){
    char str[99];
    int len;
    scanf("%s", &str);
    len = strlen(str);

    printf("%c\n", str[len/2]);
}