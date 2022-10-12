#include <stdio.h>
int main(void){
    int X,Y,N; /* 入力値 */
    int min_price; /* 最低金額 */

    char str[20]; /* 文字列格納用バッファ */

    /* 文字列をバッファに格納（改行込み） */
    fgets(str, sizeof(str), stdin);

    /* 変数に値を格納 */
    sscanf(str, "%d %d %d\n", &X, &Y, &N);

    if( X * 3 > Y ){
    	/* 3個セットの方が1個あたり安い場合 */
    	min_price = Y * ( N / 3 ) + X * ( N % 3 );
    } else {
    	/* 3個セットの方が1個あたり高い場合 */
    	min_price = X * N;
    }

        printf("%d\n", min_price);
    return 0;
}
