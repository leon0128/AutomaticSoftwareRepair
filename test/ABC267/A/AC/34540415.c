#include<stdio.h>
#include<string.h>
#define rep(i,n) for(int i = 0; i < (n); i++)

int main(void){
    /* 定義, 入力 */
    char s[10];
    scanf("%s", s);
    int ans;

    /* 動作 */
    if(strcmp(s,"Monday")==0) ans = 5;
    if(strcmp(s,"Tuesday")==0) ans = 4;
    if(strcmp(s,"Wednesday")==0) ans = 3;
    if(strcmp(s,"Thursday")==0) ans = 2;
    if(strcmp(s,"Friday")==0) ans = 1;

    /* 出力 */
    printf("%d\n", ans);

    /* 後処理 */

    return 0;
}