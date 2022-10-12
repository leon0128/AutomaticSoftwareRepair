#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG
FILE *st;
#else
#define st stdin
#endif

int main() {

#ifdef DEBUG
    st = fopen("./input.txt", "r");
#endif

    char c;
    fscanf(st, "%c", &c);
    fscanf(st, "%c", &c);
    switch (c) {
        case 'o':
            printf("5\n");
            return 0;
        case 'u':
            printf("4\n");
            return 0;
        case 'e':
            printf("3\n");
            return 0;
        case 'h':
            printf("2\n");
            return 0;
        default:
            printf("1\n");
            return 0;
    }
    
#ifdef DEBUG
    fclose(st);
#endif
    return 0;
}
