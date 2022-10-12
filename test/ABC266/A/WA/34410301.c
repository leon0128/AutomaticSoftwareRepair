#include <stdio.h>
#include <string.h>

int main(void) {
    long N = 0;
    int ans = 0;
    if (scanf("%ld", &N) == 1) {
    //文字列データが変数 string に正しく受け取れた場合
    } else {
    //文字列データは変数 string には受け取れてない。よって、変数 string の中身にアクセスしてはいけない。内容はゴミ。
    }
    if (N < 0){
        ans = 998244353 + (N % 998244353);
    }else{
        ans = N % 998244353;
    }
    printf("%d", ans);
    return 0;
}