#include <stdio.h>
int main(void){
    int leng,sum=0,i=0,j=0;

    scanf("%d",&leng);
    leng = leng-1;
    int ax[100];
      
    while(i<=leng){
        scanf("%d",&ax[i]);
        i++;
      }

    while(j<=leng){
        sum = sum + ax[j];
        j++;
    }
    
    printf("%d",sum);
  return 0;
}