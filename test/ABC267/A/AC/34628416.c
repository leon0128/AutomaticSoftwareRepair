#include<stdio.h>
#include<string.h>
int main(){
    char str[10];
    scanf("%s", str);
    if(strcmp(str, "Monday")==0)printf("%d\n", 5);
    else if(strcmp(str, "Tuesday")==0)printf("%d\n", 4);
    else if(strcmp(str, "Wednesday")==0)printf("%d\n", 3);
    else if(strcmp(str, "Thursday")==0)printf("%d\n", 2);
    else printf("%d\n", 1);
    return 0;
}