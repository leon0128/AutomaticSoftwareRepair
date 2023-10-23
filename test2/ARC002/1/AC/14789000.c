#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
#include<limits.h>
int main(){
    int Y;
    scanf("%d",&Y);
    int f = 0;
    if(Y % 4 == 0) f = 1;
    if(Y % 100 == 0) f = 0;
    if(Y % 400 == 0) f = 1;
    if(f) printf("YES\n");
    else printf("NO\n");
}
