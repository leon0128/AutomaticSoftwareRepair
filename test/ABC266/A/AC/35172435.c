#include <stdio.h>

int main() {
    char S[99];
    scanf("%s",S);
    int x=0;
    int i;
    for(i=0;S[i]!='\0';i++);
    int s=i/2;
    printf("%c\n",S[s]);
    return 0;
}