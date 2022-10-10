#include <stdio.h>

int a[107];

int main(){
	int n, ans = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		ans += a[i];
	}
	printf("%d", ans);
	return 0;
}