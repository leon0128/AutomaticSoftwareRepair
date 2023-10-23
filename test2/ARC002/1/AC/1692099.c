#include <stdio.h>
int uru(int y){
    int count=0;
    if(y%4==0)count++;
    if(y%100==0)count++;
    if(y%400==0||count==1)return 1;
    return 0;
}
int main(void){
    int y;
    scanf("%d",&y);
    if(uru(y))printf("YES\n");
    else printf("NO\n");
}
