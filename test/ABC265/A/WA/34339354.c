#include<stdio.h>
#include<stdlib.h>
int main(){
    int N,M,T;
    int i,j;
    int *a=NULL;
    int *x=NULL;
    int *y=NULL;
    int *z=NULL;

    scanf("%d %d %d",&N,&M,&T);

   a=(int *)calloc(N,sizeof(int));
    
for(i=1;i<N;++i){
   scanf("%d",&a[i]);
}
   

    x=(int *)calloc(M,sizeof(int));
    y=(int *)calloc(M,sizeof(int));
    z=(int *)calloc(N,sizeof(int));
    

    for(i=0;i<M;++i){     
        scanf("%d %d",&x[i],&y[i]);
    }



    int t=0;
    for(i=0;i<M;++i){
        t=x[i];
        z[t]=y[i];
    
    }


    int sum=T;
    for(j=1;j<N;++j){
       
        if(sum<=a[j]){
          printf("No\n");
          return 0;
        }
        sum=sum-a[j];
        sum=sum+z[j+1];
    
    }
    printf("Yes\n");

    free(a);
    free(x);
    free(y);
    free(z);
   
    return 0;
}