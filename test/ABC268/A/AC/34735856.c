#include <stdio.h>

int main() {
int nums[101] = {0},i,x,counter;
for(i=0;i<5;i++) {
  scanf("%d ",&x);
  nums[x]= 1;
}
  counter = 0;
for(i=0;i<=100;i++) {
	if (nums[i] == 1) {
  		counter++;
    }
}
printf("%d\n",counter);
return 0;
}