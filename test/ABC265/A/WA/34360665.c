#include <stdio.h>
#include <stdlib.h>

int main(){
  int i,j;
  int n,m,t;
  int toral_time=0;
  
  scanf("%d %d %d",&n,&m,&t);
  /* printf("%d %d %d\n",n,m,t); */
  
  int *a;
  int *x;
  int *y;

  if((a=(int*)malloc((n-1)*sizeof(int))) ==NULL){
    fprintf(stderr,"memory error");
    exit(1);
  }
  if((x=(int*)malloc(m*sizeof(int))) ==NULL){
    fprintf(stderr,"memory error");
    exit(1);
  }
  if((y=(int*)malloc(m*sizeof(int))) ==NULL){
    fprintf(stderr,"memory error");
    exit(1);
  }

  for(i=0; i<n-1; i++){
    scanf("%d",&a[i]);
  }
  for(i=0; i<m; i++){
    scanf("%d %d",&x[i],&y[i]);
  }

  
  /* for(i=0; i<n-1; i++){ */
  /*   printf("%d ",a[i]); */
  /* } */
  /* for(i=0; i<m; i++){ */
  /*   printf("%d %d \n",x[i],y[i]); */
  /* } */

  for(i=0; i<m; i++){
    a[x[i]] -= y[i];
  }

  for(i=0; i<n-1; i++){
    t -= a[i];
  }

  if(t>0){
    printf("Yes\n");
  }else{
    printf("No\n");
  }

  free(a);
  free(x);
  free(y);
}
