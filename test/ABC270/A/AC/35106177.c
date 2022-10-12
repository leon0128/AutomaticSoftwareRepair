#include <stdio.h>

int main(void)
{
    int a, b, Takahashi[3], Aoki[3], Sunuke = 0;
    scanf("%d %d", &a, &b);
    for (int i = 0; i < 3; i++) {
        Takahashi[i] = 0;
        Aoki[i] = 0;
    }
    switch(a) {
        case 1:
            Takahashi[0] = 1;
            break;
        case 2:
            Takahashi[1] = 1;
            break;
        case 3:
            Takahashi[0] = 1;
            Takahashi[1] = 1;
            break;
        case 4:
            Takahashi[2] = 1;
            break;
        case 5:
            Takahashi[0] = 1;
            Takahashi[2] = 1;
            break;
        case 6:
            Takahashi[1] = 1;
            Takahashi[2] = 1;
            break;
        case 7:
            Takahashi[0] = 1;
            Takahashi[1] = 1;
            Takahashi[2] = 1;
            break;
    }

    switch(b) {
        case 1:
            Aoki[0] = 1;
            break;
        case 2:
            Aoki[1] = 1;
            break;
        case 3:
            Aoki[0] = 1;
            Aoki[1] = 1;
            break;
        case 4:
            Aoki[2] = 1;
            break;
        case 5:
            Aoki[0] = 1;
            Aoki[2] = 1;
            break;
        case 6:
            Aoki[1] = 1;
            Aoki[2] = 1;
            break;
        case 7:
            Aoki[0] = 1;
            Aoki[1] = 1;
            Aoki[2] = 1;
            break;
    }

    if (Takahashi[0] == 1)
        Sunuke += 1;
    else if (Aoki[0] == 1)
        Sunuke += 1;
    if (Takahashi[1] == 1)
        Sunuke += 2;
    else if (Aoki[1] == 1)
        Sunuke += 2;
    if (Takahashi[2] == 1)
        Sunuke += 4;
    else if (Aoki[2] == 1)
        Sunuke += 4;

    printf("%d", Sunuke);
    return 0;
}