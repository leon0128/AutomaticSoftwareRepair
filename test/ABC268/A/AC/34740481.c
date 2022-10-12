#include<stdio.h>

int main()
{
  int a[5];
  int type = 5;
  int b[5] = {};  // 同種類が合ったらそれのインデックスを記憶、次回ループからは飛ばす
  for(int i=1; i <= 5; ++i)
  {
    scanf("%d", &a[i]);
  }

  for(int i=1; i < 5; ++i)
  {
    if(a[i] == a[i+1] || a[i] == a[i+2] ||a[i] == a[i+3] ||a[i] == a[i+4])
    {
      --type;
    }
    // for(int j=i+1; j <= 5; ++j)
    // {
    //   if(a[i] == a[j] && b[j] == 0)
    //   {
    //     b[i] = i;
    //     b[j] = j;
    //     --type;
    //   }
    // }
  }
  printf("%d", type);
}
