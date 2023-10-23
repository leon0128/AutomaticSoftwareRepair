/*
  第4回ユニリタプログラミングコンテスト～練習サイト～
  C言語用
  ファイル名 qA.c
  作成者 228 金子幸裕 2017/06/14 18:10
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main( void )
{
    int nyear;

    scanf( "%d" , &nyear );

    if ( ( nyear % 4 ) == 0 && (( nyear % 100 ) != 0 || ( nyear % 400 ) == 0) )
    {
        printf("YES");
    }
    else
    {
        printf("NO");
    }

    printf("\n");

    return ( 0 );

}
