#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char S[110];
    int T;
    scanf("%s",S);
    T = strlen(S);
    printf("%c\n",S[((T+1)/2)-1]);
    return 0;
}