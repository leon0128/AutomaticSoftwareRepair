#include <stdio.h>

typedef struct {
    unsigned char b0:1;
    unsigned char b1:1;
    unsigned char b2:1;
    unsigned char b3:1;
    unsigned char b4:1;
    unsigned char b5:1;
    unsigned char b6:1;
    unsigned char b7:1;
} st_flag8;

typedef  union {
    st_flag8 bit;
    unsigned char flag;
  } flag8;

int main()
{
    int i_a, i_b;
    flag8 a;
    flag8 b;
    flag8 c;

    scanf("%d %d", &i_a, &i_b);
    a.flag = i_a;
    b.flag = i_b;

    c.flag = a.flag | b.flag;

    printf("%d\n", c.flag);

    return 0;
}
