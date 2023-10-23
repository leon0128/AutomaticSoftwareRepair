#include <stdio.h>
#include <stdlib.h>

int main()
{
    int y,uru,yn=0;

    scanf("%d",&y);

    if(y%4==0){
        uru=1;
        yn=1;
    }
    if(y%100==0){
        uru=0;
        yn=1;
    }
    if(y%400==0){
        uru=1;
        yn=1;
    }

    if(yn==0)uru=0;

    if(uru==1){
        printf("YES\n");
    }else{
        printf("NO\n");
    }

    return 0;
}
