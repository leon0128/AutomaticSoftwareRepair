
#include <stdio.h>

int main()
{
    int y;
    scanf("%d",&y);
    if(y%400==0){
        printf("YES\n");
        return 0;
    }
    if(y%100==0){
        printf("NO\n");
        return 0;
    }
    if(y%4==0){
        printf("YES\n");
        return 0;
    }
    printf("NO\n");

    return 0;
}
