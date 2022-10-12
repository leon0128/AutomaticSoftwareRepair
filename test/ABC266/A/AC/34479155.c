#include <stdio.h>

int main(){
    char input[100];
    scanf("%s", input);
    int i = 0;
    while(input[i] != '\0'){
        i++;
    }
    printf("%c\n", input[((i + 1) / 2) - 1]);
    return 0;
}