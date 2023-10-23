#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

int main(void){
    int Y;
    scanf("%d",&Y);
    bool ans=false;
    if(Y%4==0){
        if(Y%100==0){
            if(Y%400==0) ans=true;
            else ans=false;
        }
        else ans=true;
    }
    else ans=false;
    if(ans) printf("YES\n");
    else printf("NO\n");
}