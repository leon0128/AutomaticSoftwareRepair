#include <stdio.h>

int main(void)
{
    int n, i;
    int num[2];
    char answer[2];

    //入力を受け取る
    scanf("%d", &n);

    //10進数を16進数に変換する
    num[1] = n % 16;//1の位
    num[0] = n / 16;//16の位
    
    for (i = 0; 2 > i; i++) {
        if (num[i] > 9) {
            answer[i] = num[i] + 'A' - 10;
        }
        else {
            answer[i] = '0' + num[i];
        }
    }

    //出力する
    printf("%c%c\n", answer[0], answer[1]);
}