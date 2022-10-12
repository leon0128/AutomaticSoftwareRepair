#include <stdio.h>
#include <stdlib.h>


int main()
{
    int a[5];
    int i, j, temp;
    int count = 1;
    for (int i = 0; i<5; i++){
        scanf("%d", &a[i]);
    }

      for (i=0; i<5; ++i) {
        for (j=i+1; j<5; ++j) {
            if (a[i] > a[j]) {
              temp =  a[i];
              a[i] = a[j];
              a[j] = temp;
            }
          }
      }

      for (i=1; i<5; i++){
        if (a[i]!= a[i-1])
            count++;
      }


    printf("%d", count);

    return 0;

}
