#include <stdio.h>

int main ()
{
    char S[16];
    int days = 0;
    scanf("%s", S);

    if(S == "Monday"){
        days = 5;
    }else if(S == "Tuesday"){
        days = 4;
    }else if(S == "Wednesday"){
        days = 3;
    }else if(S == "Thursday"){
        days = 2;
    }else{
        days = 1;
    }

    printf("%d", days);
    return 0;
}