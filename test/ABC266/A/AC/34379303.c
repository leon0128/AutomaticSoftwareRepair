/*
 * A-Middle Letter
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main( int argc, char **argv )
{
    char S[100];
    int i,n;
    char c;

    //n = scanf("%s",S);
    i = fscanf(stdin,"%s",S);
    n = strlen(S);
    //printf("%d -> %d\n", n, (n/2)+1 );
    printf("%c\n", S[n/2] );

    return 0;
}

