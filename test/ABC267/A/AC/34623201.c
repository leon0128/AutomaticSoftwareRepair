#include<stdio.h>
int main()
{
    char S[30];
    gets(S);

    char S1[]="Friday";
    char S2[]="Thursday";
    char S3[]="Wednesday";
    char S4[]="Tuesday";
    char S5[]="Monday";

    int d1  = strcmp(S,S1);

    if(d1==0)
        printf("1\n");

    int d2 = strcmp(S,S2);

    if(d2==0)
        printf("2\n");

    int d3 = strcmp(S,S3);

    if(d3==0)
        printf("3\n");

    int d4 = strcmp(S,S4);

    if(d4==0)
        printf("4\n");

    int d5 = strcmp(S,S5);

    if(d5==0)
        printf("5\n");




    return 0;








}
