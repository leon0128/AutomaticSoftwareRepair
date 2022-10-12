#include <stdio.h>
int countDistinct(int a[], int n)
{


   int i, j, count = 1;

   for (i = 1; i < n; i++)
   {
      for (j = 0; j < i; j++)
      {
         if (a[i] == a[j])
         {
            break;
         }
      }
      if (i == j)
      {
         count++;
      }
   }
   return count;
}
int main()
{
    int n;
    scanf("%d",&n);

    int a[n];
    for (int i=0;i<n;i++)
    scanf("%d",&a[i]);

    int c= countDistinct(a,n);
    printf("%d",c);
    return 0;
}
