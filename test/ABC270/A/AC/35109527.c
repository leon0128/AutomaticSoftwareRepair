#include <stdio.h>
int main(void){
    // 1
    // 2
    // 4
    // 1 2 3(1+2) 4 5(1+4) 6(2+4) 7(1+2+4)
    int A,B;
    int a[3] =  {0,0,0} ,b[3] = {0,0,0};
    
    scanf("%d %d",&A,&B);
    
    switch(A){
        case 0:
        break;
        case 1:
            a[0] = 1;
        break;
        case 2:
            a[1] = 1;
        break;
        case 3:
            a[0] = 1;
            a[1] = 1;
        break;
        case 4:
            a[2] = 1;
        break;
        case 5:
            a[0] = 1;
            a[2] = 1;
        break;
        case 6:
            a[1] = 1;
            a[2] = 1;
        break;
        case 7:
            a[0] = 1;
            a[1] = 1;
            a[2] = 1;
        break;
    }
    
    switch(B){
        case 0:
        break;
        case 1:
            b[0] = 1;
        break;
        case 2:
            b[1] = 1;
        break;
        case 3:
            b[0] = 1;
            b[1] = 1;
        break;
        case 4:
            b[2] = 1;
        break;
        case 5:
            b[0] = 1;
            b[2] = 1;
        break;
        case 6:
            b[1] = 1;
            b[2] = 1;
        break;
        case 7:
            b[0] = 1;
            b[1] = 1;
            b[2] = 1;
        break;
    }
    
    int pnt = 0;
    
    for(int i=0;i<3;i++){
        if(a[i] + b[i] >= 1){
            if(i == 0) pnt += 1;
            if(i == 1) pnt += 2;
            if(i == 2) pnt += 4;
        }
    }
    
    printf("%d\n",pnt);
}
