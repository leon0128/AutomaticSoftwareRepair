#include <stdio.h>

int main(void) {
    char S[20], c;
    scanf("%s", S);
    c=S[1];
    if (c=='o') printf("5");
    if (c=='u') printf("4");
    if (c=='e') printf("3");
    if (c=='h') printf("2");
    if (c=='r') printf("1");
    return 0;
}