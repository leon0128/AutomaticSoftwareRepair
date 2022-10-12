#include<stdio.h>
#include<stdlib.h>
int main(){
    int N,M,T;
    int i,j;
    scanf("%d %d %d",&N,&M,&T);
     (void)getchar();

   int *a=calloc(N,sizeof(int));
    
for(i=0;i<N-1;++i){
   scanf("%d",&a[i]);
}

    
    int *z=calloc(M,sizeof(int));
    int *y=calloc(M,sizeof(int));
    int *x=calloc(M,sizeof(int));

   (void)getchar();
 
    

    for(i=0;i<M;++i){     
        scanf("%d %d",&z[i],&y[i]);
    }
    
    int t;
    for(i=0;i<M;++i){
        t=y[i];
        x[t]=t;
    }


    int sum=0;
    for(j=0;j<N-1;++j){
        sum=sum+x[i]-a[i];
        if(sum+x[i]-a[i]<0){
          printf("No\n");
          return 0;
        }

    }
    printf("Yes\n");
    return 0;
}