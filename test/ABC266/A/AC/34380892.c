#include <stdio.h>
#include <string.h> 

int main() {

    int t, n;
    char a[100];
    scanf ("%s", a);
    int p = strlen(a);
    int q = (p + 1) / 2;
    printf ("%c\n", a[q - 1]);
    return 0;
}