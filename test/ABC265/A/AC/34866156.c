#include <stdio.h>

int main (int argc, char const argv[]){
    int x,y,n;
    scanf("%d%d%d",&x,&y,&n);
    int three = 0;
    int final =0;
    if(y>x*3){
        final = n*x;
      	printf("%d",final);
      	return 0;
    }
    if(n>3){
        three = n /3;
        n -= three *3;
        final = three * y + x*n;
    }else{
        final = x*n;
    }
  	printf("%d",final);
    return 0;
}

