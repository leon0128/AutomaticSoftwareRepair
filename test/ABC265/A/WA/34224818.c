#include <stdio.h>
int main(void){
    int x,y,n,min;
    int count=0;
    int c[100][100];
    scanf("%d %d %d",&x,&y,&n);

    for(int i=1;i<=100;i++){
        for(int j=1;j<=100;j++){
            c[i][j]=i*x+j*y;

            if(i+3*j==n){
                count++;
                if(count==1){
                min=c[i][j];
                }
                if(count!=1 && c[i][j]<min){
                    min=c[i][j];
                }
            }

        }
    }
    printf("%d\n",min);

    return 0;
}