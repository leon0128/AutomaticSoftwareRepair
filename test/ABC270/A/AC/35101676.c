#include <stdio.h>

int main (void) {
    int a, b;
    scanf("%d %d",&a, &b);
    int takahashi[3], aoki[3], sunuke[3];
    int ans = 0;

    for (int i = 0; i < 3; i++) {
        takahashi[i] = 0;
        aoki[i] = 0;
        sunuke[i] = 0;
    }

    if (a == 1) {
        takahashi[0] = 1;
    } else if (a == 2) {
        takahashi[1] = 1;
    } else if (a == 3) {
        takahashi[0] = 1;
        takahashi[1] = 1;
    } else if (a == 4) {
        takahashi[2] = 1;
    } else if (a == 5) {
        takahashi[0] = 1;
        takahashi[2] = 1;
    } else if (a == 6) {
        takahashi[1] = 1;
        takahashi[2] = 1;
    } else if (a == 7) {
        takahashi[0] = 1;
        takahashi[1] = 1;
        takahashi[2] = 1;
    }

    if (b == 1) {
        aoki[0] = 1;
    } else if (b == 2) {
        aoki[1] = 1;
    } else if (b == 3) {
        aoki[0] = 1;
        aoki[1] = 1;
    } else if (b == 4) {
        aoki[2] = 1;
    } else if (b == 5) {
        aoki[0] = 1;
        aoki[2] = 1;
    } else if (b == 6) {
        aoki[1] = 1;
        aoki[2] = 1;
    } else if (b == 7) {
        aoki[0] = 1;
        aoki[1] = 1;
        aoki[2] = 1;
    }
    
    for (int i = 0; i < 3; i++) {
        if (takahashi[i] == 0 && aoki[i] == 0) {
            sunuke[i] = 0;
        } else {
            sunuke[i] = 1;
        }
    }

    if (sunuke[0] == 1) {
        ans += 1;
    }
    if (sunuke[1] == 1) {
        ans += 2;
    }
    if (sunuke[2] == 1) {
        ans += 4;
    } 

    printf("%d\n",ans);
    return 0;
}