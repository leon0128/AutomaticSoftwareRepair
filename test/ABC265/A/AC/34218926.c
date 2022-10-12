#include<stdio.h>

int main()
{
    int a, b, c;

    int en = 0;
    int count = 0;
    // スペース区切りの整数の入力
    scanf("%d %d %d", &a,  &b, &c);

    if (a * 3 > b) {
        while (c >= count * 3) {
            count += 1;
        }
        count -= 1;
        en = count * b + (c - count * 3) * a;
    }
    else {
        en = a * c;
    }



   
    printf("%d", en);
    return 0;

}