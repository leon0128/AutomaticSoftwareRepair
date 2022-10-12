#include<stdio.h>
#include<string.h>

int main(void){
    /* 定義, 入力 */
    char s[100];
    scanf("%s", s);
    int l, dex;

    /* 動作 */
    l = strlen(s);
    dex = (l + 1) / 2 - 1;

    /* 出力 */
    printf("%c\n", s[dex]);

    /* 後処理 */

    return 0;
}