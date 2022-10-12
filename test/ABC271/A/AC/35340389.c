#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void)
{
  int n, i;
scanf("%d", &n);
 char A[16];
 A[0]='0';
 A[10]='A';
 for(i=0;i<16;i++){
    if(i<10){A[i]=A[0]+i;}
    else{A[i]=A[10]+i-10;}
 }
 
 

if(n<16){
    printf("0"); 
    printf("%c", A[n]);
}
else {printf("%c%c", A[n/16], A[n%16]);
}
  return 0;
}