#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG
FILE *st;
#else
#define st stdin
#endif

void decToHexa(int n) {
    // char array to store hexadecimal number
    char hexaDeciNum[2] = {'0', '0'}; 
    // counter for hexadecimal number array
    int i = 0;
    while (n != 0) {
        // temporary variable to store remainder
        int temp = 0; 
        // storing remainder in temp variable.
        temp = n % 16; 
        // check if temp < 10
        if (temp < 10) {
            hexaDeciNum[i] = temp + 48;
            i++;
        } else {
            hexaDeciNum[i] = temp + 55;
            i++;
        } 
        n = n / 16;
    } 
    // printing hexadecimal number array in reverse order
    printf("%c%c\n", hexaDeciNum[1], hexaDeciNum[0]);
}

int main() {

#ifdef DEBUG
    st = fopen("./input.txt", "r");
#endif

    int n;
    fscanf(st, "%d", &n);
    decToHexa(n);

#ifdef DEBUG
    fclose(st);
#endif
    return 0;
}
