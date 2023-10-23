#include <stdio.h>

int main(){
    int year;

    scanf("%d", &year);

    if(year%400==0){
        printf("YES\n");
        return 0;
    }
    else if(year%100==0){
        printf("NO\n");
        return 0;
    }
    else if(year%4==0){
        printf("YES\n");
        return 0;
    }
    else {
        printf("NO\n");
        return 0;
    }
    return 0;

}
