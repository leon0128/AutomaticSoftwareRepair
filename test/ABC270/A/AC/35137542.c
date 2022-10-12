#include <stdio.h>

int main(void){
	int a, b, c[3] = {}, d[3] = {}, e[3] = {4, 2, 1};

	scanf("%d%d", &a, &b);

	int i = 0;
	while(a > 0){
		if(a - e[i] >= 0){
			d[i]++;
			a -= e[i];
		}
		i++;
	}

	i = 0;
	while(b > 0){
		if(b - e[i] >= 0){
			c[i]++;
			b -= e[i];
		}
		i++;
	}

	int sum = 0;
	for(int i = 0; i < 3; i++){
		if(d[i] == 1 || c[i] == 1){
			sum += e[i];
		}
	}

	printf("%d\n", sum);
	return (0);
}