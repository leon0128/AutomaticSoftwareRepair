#include <stdio.h>
#include <string.h>

int main ()
{
    char S[16];
    int days = 0;
    (void)scanf("%s", &S[0]);

    if(strcmp(S, "Monday")){
        days = 5;
    }else if(strcmp(S, "Tuesday")){
        days = 4;
    }else if(strcmp(S, "Wednesday")){
        days = 3;
    }else if(strcmp(S, "Thursday")){
        days = 2;
    }else{
        days = 1;
    }

    printf("%d\n", days);
    return 0;
}