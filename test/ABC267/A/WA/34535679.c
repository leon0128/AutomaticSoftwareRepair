//267-a

#include <stdio.h>
#include <string.h>

int main(void){
    char s[20];
    scanf("%s",s);
    if(s == "Monday"){
        printf("5\n");
        return 0;
    } else if(s == "Tuesday"){
        printf("4\n");
        return 0;
    } else if(s == "Wednesday"){
        printf("3\n");
        return 0;
    } else if(s == "Thursday"){
        printf("2\n");
        return 0;
    } else {
        printf("1\n");
        return 0;
    }

    return 0;
}