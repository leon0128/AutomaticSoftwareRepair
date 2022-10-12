#include<stdio.h>

main()

{

int n,i;

scanf("%d",&n);

int a[n];

for(i=0;i<n;i++)

scanf("%d",&a[i]);

if(n%2==0)

printf("%d,%d",a[n/2-1],a[n/2]);

else

printf("%d",a[n/2]);

}
