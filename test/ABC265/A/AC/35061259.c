#include <stdio.h>

int main (void)
{
    int X , Y , N ;
    scanf("%d %d %d", & X , & Y , & N);
   if( X * 3 < Y){
    printf("%d\n", X * N);
   } 
   else if( N % 3 == 0){
    printf("%d\n", N / 3 * Y);
   }
    else if( N % 3 == 1){
        printf("%d\n", (N / 3 * Y) + X) ;
    }
    else {
        printf("%d\n", (N / 3 * Y) + ( X * 2)) ;
    }
   return 0 ;
}