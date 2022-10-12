#include <stdio.h>
#include <string.h>
int main(void){
    char moji[99];
    int p;
    scanf("%s", moji);
    p = strlen(moji) / 2;
    printf("%c", moji[p]);
}