#include<stdio.h>
#include<math.h>
#include<string.h>

int main(void)
{
  int d; //入力値d
  char x[17] = "0123456789ABCDEF"; //16進数の配列
  char x0[2] = {0}; //16進数の右から1ケタめ
  char x1[2] = {0}; //16進数の右から2ケタめ
  char x2[2] = {0}; //16進数の右から3ケタめ
  char x3[2] = {0}; //16進数の右から4ケタめ
  char x4[2] = {0}; //16進数の右から5ケタめ
  char xfin[6] = {0}; //16進数に変換した結果
  int L; //ループ用変数L
  int xv0,xv1,xv2,xv3,xv4; //16進数のそれぞれの桁の重み

  printf("0から1048575までの10進数の整数値を入力。＞");
  scanf("%d",&d); //dに10進数の整数値が入る。
	
  /*16進数の計算*/
  xv0 = (int)(d/(pow(16,0)))%16; //16^0の位
  xv1 = (int)(d/(pow(16,1)))%16; //16^1の位
  xv2 = (int)(d/(pow(16,2)))%16; //16^2の位
  xv3 = (int)(d/(pow(16,3)))%16; //16^3の位
  xv4 = (int)(d/(pow(16,4)))%16; //16^4の位

  for(L=0; L<16; L=L+1)
  {
    if(xv0==L)
    {
      strncpy(x0,x+L,1); //x0に、配列xのL番めからの値を1つ分代入する。
    }
    if(xv1==L)
    {
      strncpy(x1,x+L,1); //x1に、配列xのL番めからの値を1つ分代入する。
    }
    if(xv2==L)
    {
      strncpy(x2,x+L,1); //x2に、配列xのL番めからの値を1つ分代入する。
    }
    if(xv3==L)
    {
      strncpy(x3,x+L,1); //x3に、配列xのL番めからの値を1つ分代入する。
    }
    if(xv4==L)
    {
      strncpy(x4,x+L,1); //x4に、配列xのL番めからの値を1つ分代入する。
    }
  }

  snprintf(xfin,6,"%s%s%s%s%s",x4,x3,x2,x1,x0); //xfinにx4～x0を連結させたものを代入する。
  printf("%d（10進数） = %s（16進数）\n",d,xfin); //16進数に変換した結果を出力する。
  
  return(0);
}