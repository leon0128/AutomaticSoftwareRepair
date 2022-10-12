//
//  ABC268A.c
//  
//
//  Created by k18070kk on 2022/09/10.
//

#include <stdio.h>
int main(){
    int x[5];
    scanf("%d %d %d %d %d\n", &x[0], &x[1], &x[2], &x[3], &x[4]);
    int xloop,xmax,yloop,ymax,Ymax,find;
    int y[10];
    xmax = sizeof(x)/sizeof(int);
    y[0]=x[0];
    ymax=1;
    for(xloop=1; xloop<xmax; xloop++){
        for(yloop=0; yloop<ymax; yloop++){
            find = 0;
            if(x[xloop] == y[yloop]){
                find =1;
                break;
            }
        }
        if(find == 0){
            y[ymax]=x[xloop];
            ymax++;
        }
    }
    Ymax = sizeof(y)/sizeof(int);
    for(int h=0;h<ymax;h++){
      	printf("%d ", y[h]);
        //printf("h=%d:y[h]=%d    ", h, y[h]);
    }
  	//printf("YMAX===%d    ", ymax);
    //printf("%d %d %d %d %d\n", y[0], y[1], y[2], y[3], y[4]);
    return 0;
}
