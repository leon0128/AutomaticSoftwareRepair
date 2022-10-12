#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv)
{
        int     a;
        int     b;
        int     sunuke;

        scanf("%d %d", &a, &b);
#ifdef TRACE
        printf("A:%d. B:%d\n", a, b);
#endif
        sunuke = (a | b);

        printf("%d\n", sunuke);
}
