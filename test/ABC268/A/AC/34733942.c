#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(void){
    int a,b,c,d,e, ans=5;
    scanf("%d %d %d %d %d", &a, &b, &c, &d, &e);
    if(a == b){
        ans--;
    }else if(a == c){
        ans--;
    }else if(a == d){
        ans--;
    }else if(a == e){
        ans--;
    }
    if(b == c){
        ans--;
    }else if(b == d){
        ans--;
    }else if(b == e){
        ans--;
    }
    if(c == d){
        ans--;
    }else if(c == e){
        ans--;
    }
    if(d == e){
        ans--;
    }
    printf("%d", ans);    
}