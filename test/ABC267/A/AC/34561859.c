#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char str[100];
    char s1[100]={'M','o','n','d','a','y'},
    s2[100]={'T','u','e','s','d','a','y'},
    s3[100]={'W','e','d','n','e','s','d','a','y'},
    s4[100]={'T','h','u','r','s','d','a','y'},
    s5[100]={'F','r','i','d','a','y'},
    s6[100]={'S','a','t','u','r','d','a','y'},
    s7[100]={'S','u','n','d','a','y'};
    scanf("%s",str);
    if(strcmp(str,s1)==0)
        printf("5");
    if(strcmp(str,s2)==0)
        printf("4");
    if(strcmp(str,s3)==0)
        printf("3");
    if(strcmp(str,s4)==0)
        printf("2");
    if(strcmp(str,s5)==0)
        printf("1");
    if(strcmp(str,s6)==0)
        printf("0");
    if(strcmp(str,s7)==0)
        printf("6");
    return 0;
}
