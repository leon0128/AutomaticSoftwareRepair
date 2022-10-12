#include <stdio.h>
#include <string.h>
int main(void){
    int n; char c[101]; 
    scanf("%s",c);
    n=strlen(c);
    n/=2;
    printf("%c",c[n]);
    
}
