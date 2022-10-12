#include<stdio.h>
#define rep(i,n) for(int i = 0; i < (n); i++)
#define ll long long

int main(void){
    /* 定義, 入力 */
    int x, y, n;
    scanf("%d%d%d", &x, &y, &n);
    int ans = 0;

    /* 動作 */
    if( (double)y/3.0 < (double)x ){
        ans += (n / 3) * y;
        n %= 3;
        ans += n * x;
    }
    else ans += n * x;

    /* 出力 */
    printf("%d\n", ans);

    /* 後処理 */

    return 0;
}