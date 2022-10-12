#include <stdio.h>

int main() {
	int n, m, t;
	int a[100000];//a[3]==6なら，３から4に行くときに，６消費する
	int bonus[100000] = { 0 };//bonus[3]==4なら，３番目で4回復する

	//scanf_s("%d %d %d", &n, &m, &t);
	scanf("%d %d %d", &n, &m, &t);
	
	for (int i = 1; i < n; i++) {//Aのとこ　持ち時間の消費のところ
		//scanf_s("%d", &a[i]);
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= m; i++) {
		int x, y;
		//scanf_s("%d %d", &x, &y);
		scanf("%d %d", &x, &y);
		bonus[x] = y;
	}

	for (int i = 1; i < n; i++) {
		if (t <= a[i]) {
			printf("No");
			t -= a[i];
			break;
		}
		else {
			t -= a[i];
			t += bonus[i+1];
		}
	}
	if (t > 0) {
		printf("Yes");
	}
}