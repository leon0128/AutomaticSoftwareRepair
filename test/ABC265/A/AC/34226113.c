#include <stdio.h>
int main(void){
    int x,y,n,min;
    int count=0;
    int c[100][100];
    scanf("%d %d %d",&x,&y,&n);

    for(int i=0;i<=100;i++){
        for(int j=0;j<=100;j++){
            c[i][j]=i*x+j*y;

            if(i+3*j==n){
                
                count++;
                if(count==1){
                min=c[i][j];
                }
                else if(c[i][j]<min){
                    min=c[i][j];
                }else{
                    continue;
                }
            }

        }
    }
    printf("%d\n",min);
   

    return 0;
}