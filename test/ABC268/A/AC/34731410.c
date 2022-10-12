#include <stdio.h>
 
int main(){
	int a[5];
	for(int i = 0; i < 5; i++){
		scanf("%d", &a[i]);
	}

	int ans = 5;
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < i; j++){
			if(a[i] == a[j]){
				ans--;
				break;
			}
		}
	}

	printf("%d\n", ans);
	return 0;
}