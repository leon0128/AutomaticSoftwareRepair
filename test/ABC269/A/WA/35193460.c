/*整数 a,b,c,dが与えられるとき、以下の指示に従って、2行出力せよ。
　1行目は (a+b)×(c−d) の計算結果を整数として出力せよ。
　2行目は入力にかかわらず Takahashi と出力せよ。*/

#include<stdio.h>
int main(){

int buf[100];

int a,b,c,d,sum;
fgets(buf, sizeof(buf), stdin);
 sscanf(buf, "%d", &a);
fgets(buf, sizeof(buf), stdin);
 sscanf(buf, "%d", &b);
fgets(buf, sizeof(buf), stdin);
 sscanf(buf, "%d", &c);
fgets(buf, sizeof(buf), stdin);
 sscanf(buf, "%d", &d);

sum=(a+b)*(c-d);

printf("%d\n", sum);
printf("Takahashi");
}