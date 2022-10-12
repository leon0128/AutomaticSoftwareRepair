#include <stdio.h>

int main()
{
    int N;
    int A,B;
    char str[]="0123456789ABCDEF";

    scanf("%d\n",&N);

    A=N/16;
    B=N%16;

    printf("%c%c\n",str[A],str[B]);

    return 0;
}