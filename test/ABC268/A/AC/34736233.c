#include <stdio.h>
#include <stdlib.h>
int cmp(const void *p, const void *q){
    return *(int*)p-*(int*)q;
}

int main(){
   int a,b,c,d,e;
   int n[10];
   int count=0;
   n[0]=a;
   n[1]=b;
   n[2]=c;
   n[3]=d;
   n[4]=e;
   for(int i=0;i<5;i++){
    scanf("%d",&n[i]);
   }
   qsort(n,5,sizeof(int),cmp);

   for(int i=0;i<5;i++){
    if(n[i]==n[i+1])
    count++;
   }
   printf("%d\n",5-count);
    return 0;
}