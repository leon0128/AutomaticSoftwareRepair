#include <stdio.h>

void ShowHex(int x)
{
    int r;
    r = x % 16; /* １６で割った余りをrに保存 */
    x = x / 16; /* x < 16 なら０になる */

    if (x > 0)      /* x が０でない限り */
        ShowHex(x); /* １／１６小さい自分を再帰的に呼び出す */

    /* この行以降はxが０になり、再帰から戻る時実行される */

    if (r >= 0 && r <= 9)      /* rが０から９なら */
        printf("%d", r);       /* そのまま表示 */
    else if (r > 9)            /* rが９以上なら */
        putchar('A' + r - 10); /* アルファベットに変換して表示（注） */
}

int main()
{
    int n;
    scanf("%d", &n);
    if (n >= 0 && n <= 15)
    {
        putchar('0');
        if (n >= 0 && n <= 9)
        {
            printf("%d\n", n);
            return 0;
        }
        else if (n > 9 && n <= 15)
        {
            putchar('A' + (n % 16) - 10);
            printf("\n");
            return 0;
        }
    }

    ShowHex(n);
    printf("\n");
    return 0;
}