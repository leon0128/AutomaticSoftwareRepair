#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    long long int NN;
    long long int l=998244353;
    long long int x,n;
    double nmax,nmin;
    
    scanf("%lld",&NN);
    
    nmax = NN / l;
    nmin = (NN-l) / l; 

    //printf("nmax = %le nmin = %le\n",nmax,nmin);

    for(n=nmin;n<=nmax;n++){
        x = NN-n*l;
        if(x>=0 && x<=l) break;
    }
        
    //printf("x = %lld\n",x);
    printf("%lld\n",x);
}