#include <stdio.h>

int main(void) {
	int i,sum=0,l;
  scanf("%d",&l);
  int ar[l];
  for(i=0;i<l;i++)
    scanf("%d",&ar[i]);
  for(i=0;i<l;i++)
    sum=sum+ar[i];
  printf("%d",sum);
  return 0;
}
