#include <stdio.h>

int main (){
  	int N, sum_num, answer = 0;
  	int A[100] = {0};
  	
  	scanf("%d", &N);
  	
  	for(sum_num = 0; sum_num < N; sum_num++){
      	scanf("%d", &A[sum_num]);
    }
  	
  	for(sum_num = 0; sum_num < N; sum_num++){
      	answer = answer + A[sum_num];
    }
  	
  	printf("%d", answer);
}