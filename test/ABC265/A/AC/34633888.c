#include <stdio.h>

int main() {
	int x, y, n;
	int sum;

	//scanf_s("%d %d %d", &x, &y, &n);
	scanf("%d %d %d", &x, &y, &n);

	if (3 * x <= y) {//この場合全部x円のりんごを1個買うことをする
		sum = x * n;
	}
	else {//できるだけy円でりんご3個買い，残りを1つずつ買う
		sum = y * (n / 3) + x * (n % 3);
	}

	printf("%d", sum);
}