/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>

int main()
{
    int A,B,C,D,E;
    scanf("%d",&A);
    scanf("%d",&B);
    scanf("%d",&C);
    scanf("%d",&D);
    scanf("%d",&E);
    int count=1;
    if(B!=A){
        count++;
    }
    if(C!=B && C!=A){
        count++;
    }
    if(D!=C && D!=B && D!=A){
        count++;
    }
    if(E!=D && E!=C&&E!=B&&E!=A){
        count++;
    }
    printf("%d",count);
}
