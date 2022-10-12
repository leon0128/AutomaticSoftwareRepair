#include <stdio.h>
int main(){
    char NUM[] = "0123456789ABCDEF";
    int N;
    scanf("%d",&N);
    printf("%c%c\n",NUM[N/16],NUM[N%16]);
    return 0;
}