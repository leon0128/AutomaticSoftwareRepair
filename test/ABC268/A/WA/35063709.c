#include<stdio.h>

int main(){

        int a[7],i,j,count,k=0;
        for(i=0;i<5;i++){

            scanf("%d",&a[i]);
        }

        for(i=0;i<5;i++){

                count=0;

            for(j=0;j<5;j++){

                if(j!=i){

                        if(a[i]==a[j]){

                    count++;


                }


                }


            }

            if(count==0){

                k++;
            }


        }

        if(k==0){

            k=1;
        }

        printf("%d",k);


return 0;

}
