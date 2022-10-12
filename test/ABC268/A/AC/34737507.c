#include<stdio.h>
#include<stdlib.h>
#define rep(i,n) for(int i = 0; i < (n); i++)
#define ll long long

int main(void){
    /* 定義, 入力 */
    int a[5];
    rep(i,5)scanf("%d", &a[i]);
    int cnt = 0;

    /* 動作 */
    rep(i,101){
        rep(j,5){
            if(a[j]==i){
                cnt++;
                break;
            }
        }
    }

    /* 出力 */
    printf("%d\n", cnt);

    /* 後処理 */

    return 0;
}