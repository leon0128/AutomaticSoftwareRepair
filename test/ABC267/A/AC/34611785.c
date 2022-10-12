#include<stdio.h>
int main(){
    char s[15];
    scanf("%s",s);
    if(s[0] == 'M')puts("5");
    if(s[0] == 'T'){
        s[1] == 'u'?puts("4"):puts("2");
    }
    if(s[0] == 'W')puts("3");
    if(s[0] == 'F')puts("1");
    return 0;
}