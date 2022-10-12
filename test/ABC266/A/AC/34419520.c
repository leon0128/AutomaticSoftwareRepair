#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
int main(){
    int test;
    // scanf("%d", &test);
    test = 1;
    char s[101];
    while(test--){
        scanf("%s", s);
        int n = strlen(s);
        printf("%c\n", s[n/2]);
    }
    return 0;
    
}