#include <stdio.h>
int main(void){
    int i = 0, j = 0, k = 0;
    char buf[20];
    int num[5];
	int variation = 1, tmp = 0;

    fgets(buf, sizeof(buf), stdin);
    sscanf(buf, "%d %d %d %d %d\n", &num[0], &num[1], &num[2], &num[3], &num[4]);

	while (i < 5)
    {
      j = i;
      while (j < 5)
      {
        if(num[i] > num[j])
        {
          tmp = num[i];
          num[i] = num[j];
          num[j] = tmp;
        }
        j++;
      }
      i++;
    }
  
  	for(i=0; i<4; i++)
    {
      if(num[i] != num[i+1])
        variation++;
    }
  
  	printf("%d", variation);
  
    return 0;
}