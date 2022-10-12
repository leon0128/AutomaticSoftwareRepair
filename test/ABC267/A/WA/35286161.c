#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
	int i, j, judge[7], left, right;
	char state[11];
	scanf(" %s", &state);
	if (state[0] == '1'){
		printf("No");
		return 0;
	}
	judge[0] = state[6] - '0';
	judge[1] = state[3] - '0';
	judge[2] = state[1] + state[7] - '0' - '0';
	judge[3] = state[4] - '0';
	judge[4] = state[2] + state[8] - '0' - '0';
	judge[5] = state[5] - '0';
	judge[6] = state[9] - '0';
	
	for (i = 0; i < 7; i++)
		if (judge[i]){
			left = i;
			break;
		}
	for (i = 6; i >= 0; i--)
		if (judge[i]){
			right = i;
			break;
		}
	if (left >= right){
		printf("No");
		return 0;
	}
	for (i = left; i < right; i++)
		if (judge[i] == 0){
			printf("Yes");
			return 0;
		}
	
	printf("No");
	return 0;
}
