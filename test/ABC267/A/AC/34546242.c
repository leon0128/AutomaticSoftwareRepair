#include <stdio.h>
#include <string.h>

int main(void) {
    char str[10];
    scanf("%s", &str);
    char *m1="Monday";
    char *m2="Tuesday";
    char *m3="Wednesday";
    char *m4="Thursday";
    char *m5="Friday";
    
    if(strcmp(str,m1) == 0) printf("5\n");
    else if(strcmp(str,m2) == 0) printf("4\n");
    else if(strcmp(str,m3) == 0) printf("3\n");
    else if(strcmp(str,m4) == 0) printf("2\n");
    else if(strcmp(str,m5) == 0) printf("1\n");
    else printf("error\n");
} 