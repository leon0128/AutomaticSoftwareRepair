#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(void)
{
    int X,Y,N;
    scanf("%d%d%d",&X,&Y,&N);
    int xn=0,yn=0;
    if (3*X>Y && N>=3){
        yn=N/3;
        xn=N-(yn*3);
        int mem=10000000;
        while (yn!=0){
            int sum=0;
            sum+=yn*Y;
            sum+=xn*X;
            if (sum<mem){
                mem=sum;
            }
            yn--;
            xn+=3;
        }
        printf("%d",mem);
    } else if (3*X<=Y && N>=3) {
        xn=N;
        int mem=10000000;
        while (xn>0){
            int sum=0;
            sum+=yn*Y;
            sum+=xn*X;
            if (sum<mem){
                mem=sum;
            }
            xn-=3;
            yn++;
        }
        printf("%d",mem);
    } else {
        printf("%d",N*X);
    }
    return 0;
}